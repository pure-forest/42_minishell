#include "../../inc/execution.h"

static int	launch_single_cmd_exec(t_struct_ptrs *data, t_input *curr,
				t_exec_data *exec_data);
static void	process_all_cmds(t_struct_ptrs *data, t_exec_data *exec_data,
				int check_return_value);
static int	process_pipeline(t_struct_ptrs *data, t_input *curr,
				t_exec_data *exec_data);
static void	update_last_cmd_in_env(t_struct_ptrs *data, t_input *curr);

void	execute(t_struct_ptrs *data)
{
	t_exec_data	exec_data;
	int			check_return_value;

	init_exec_data(&exec_data);
	check_return_value = create_execute_env(data);
	if (!check_return_value || check_return_value == EMPTY)
	{
		process_all_cmds(data, &exec_data, check_return_value);
		wait_for_children(data);
	}
	signal_init();
	clean_up_exec_creations(data, NULL);
	return ;
}

static void	process_all_cmds(t_struct_ptrs *data, t_exec_data *exec_data,
		int check_return_value)
{
	t_input	*curr;

	curr = data->input;
	check_return_value = split_env_path(data, curr);
	while (curr)
	{
		if ((check_return_value == EMPTY || check_return_value == NOT_FOUND)
			&& is_builtin(curr) == NO)
		{
			set_exit_code(data, SYSTEM_FAIL);
			print_err_exe(data, curr->cmd_arr[0], 2);
			curr = (t_input *)curr->base.next;
			continue ;
		}
		update_last_cmd_in_env(data, curr);
		if (launch_single_cmd_exec(data, curr, exec_data))
			break ;
		curr = (t_input *)curr->base.next;
	}
}

static int	launch_single_cmd_exec(t_struct_ptrs *data, t_input *curr,
		t_exec_data *exec_data)
{
	int	in_pipeline;

	if (curr->base.next)
		if (pipe(exec_data->pipe_fd) == -1)
			return (set_exit_code(data, SYSTEM_FAIL), FAIL);
	in_pipeline = curr->base.prev || curr->base.next;
	if (is_builtin(curr) && !in_pipeline)
	{
		if (handle_standard_fds(data, exec_data, NO) == SYSTEM_FAIL)
			return (FAIL);
		if (check_redir_files_for_exec(data, curr, exec_data->pipe_fd))
			return (FAIL);
		if (set_std_fds(data, curr, exec_data))
			return (FAIL);
		launch_builtin(data, curr, exec_data);
		if (handle_standard_fds(data, exec_data, YES) == SYSTEM_FAIL)
			return (FAIL);
	}
	else
	{
		if (process_pipeline(data, curr, exec_data))
			return (FAIL);
	}
	return (SUCCESS);
}

int	process_pipeline(t_struct_ptrs *data, t_input *curr, t_exec_data *exec_data)
{
	exec_data->pid = fork();
	if (exec_data->pid == -1)
		return (set_exit_code(data, SYSTEM_FAIL), FAIL);
	if (exec_data->pid == 0)
	{
		signal_init_childprocess();
		run_in_child(data, curr, exec_data);
	}
	else
	{
		parent_signal();
		if (exec_data->prev_read_end != -1)
			close_fd(&exec_data->prev_read_end);
		exec_data->prev_read_end = exec_data->pipe_fd[0];
		if (curr->base.next)
			close_fd(&exec_data->pipe_fd[1]);
	}
	return (SUCCESS);
}

static void	update_last_cmd_in_env(t_struct_ptrs *data, t_input *curr)
{
	char	*last_cmd;

	last_cmd = get_var_value(data->env, "_=");
	if (!last_cmd)
		create_var_env_and_export(data, "_=", curr->cmd_arr[0]);
	else
		update_var_in_both(data->env, data->export, "_=", curr->cmd_arr[0]);
}
