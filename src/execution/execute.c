#include "../../inc/execution.h"

int		launch_cmd_exec(t_struct_ptrs *data, t_input *curr,
			t_exec_data *exec_data);
void	run_in_child(t_struct_ptrs *data, t_input *curr,
			t_exec_data *exec_data);
int		run_execve(t_struct_ptrs *data, t_input *curr);
int		process_pipeline(t_struct_ptrs *data, t_input *curr,
			t_exec_data *exec_data);
void	init_exec_data(t_exec_data *exec_data);

void execute(t_struct_ptrs *data)
{
	t_exec_data exec_data;
	t_input *curr;
	int check_return_value;

	init_exec_data(&exec_data);
	curr = data->input;
	check_return_value = create_execute_env(data);
	if (!check_return_value || check_return_value == EMPTY)
	{
		check_return_value = split_env_path(data);
		while (curr)
		{
			if ((check_return_value == EMPTY || check_return_value == NOT_FOUND) && is_builtin(curr) == NO)
			{
				set_exit_code(data, 3);
				print_err_exe(data, curr->cmd_arr[0], 2);
				curr = (t_input *)curr->base.next;
				continue;
			}
			if (launch_cmd_exec(data, curr, &exec_data))
				break;
			curr = (t_input *)curr->base.next;
		}
		wait_for_children(data);
	}
	clean_up_exec_creations(data, NULL);
	return;
}

void	init_exec_data(t_exec_data *exec_data)
{
	*exec_data = (t_exec_data){0};
	exec_data->prev_read_end = -1;
	exec_data->pipe_fd[0] = -1;
	exec_data->pipe_fd[1] = -1;
	return ;
}

int	launch_cmd_exec(t_struct_ptrs *data, t_input *curr, t_exec_data *exec_data)
{
	int	in_pipeline;

	if (curr->base.next)
		if (pipe(exec_data->pipe_fd) == -1)
			return (set_exit_code(data, -1), FAIL);	// does this exit the whole mini or just this prompt?
	in_pipeline = curr->base.prev || curr->base.next;
	if (is_builtin(curr) && !in_pipeline)
	{
		handle_standard_fds(exec_data, NO);
		if (set_std_fds(data, curr, exec_data))
			return (FAIL);
		launch_builtin(data, curr);
		handle_standard_fds(exec_data, YES);
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
		return (set_exit_code(data, -1), FAIL);
	if (exec_data->pid == 0)
		run_in_child(data, curr, exec_data);
	else
	{
		if (exec_data->prev_read_end != -1)
			close_fd(&exec_data->prev_read_end);
		exec_data->prev_read_end = exec_data->pipe_fd[0];
		if (curr->base.next)
			close_fd(&exec_data->pipe_fd[1]);
			//close_pipe_fd(exec_data->pipe_fd, exec_data->prev_read_end);
	}
	return (SUCCESS);
}

void	run_in_child(t_struct_ptrs *data, t_input *curr, t_exec_data *exec_data)
{
	if (set_std_fds(data, curr, exec_data))
	{
		//close_all_exec_fds(exec_data);
		exit (data->exit_code);
	}
	close_all_exec_fds(exec_data);
	if (!curr->cmd_arr[0])
	{
		set_exit_code(data, SUCCESS);
		clean_up_exec_creations(data, curr);
		//close_all_exec_fds(exec_data);
		mega_clean(data);
		exit (data->exit_code);
	}
	if (is_builtin(curr))
	{
		launch_builtin(data, curr);
		clean_up_exec_creations(data, curr);
		//close_all_exec_fds(exec_data);
		mega_clean(data);
		exit(data->exit_code);
	}
	else
	{
		check_if_cmd_is_path(curr);
		if (!curr->cmd_path)
		{
			make_cmd_path(data, curr);
			if (!curr->cmd_path)
			{
				set_exit_code(data, ENOENT);
				print_err_exe(data, curr->cmd_arr[0], 3);
				clean_up_exec_creations(data, curr);
				//close_all_exec_fds(exec_data);
				mega_clean(data);
				exit(data->exit_code);
			}
		}
		if (curr->cmd_path)
			if (run_execve(data, curr))
			{
				//close_all_exec_fds(exec_data);
				exit(data->exit_code);
			}
	}
}

int	run_execve(t_struct_ptrs *data, t_input *curr)
{
	if (access(curr->cmd_path, F_OK) == 0)
	{
		if (access(curr->cmd_path, X_OK) == 0)
		{
			if (execve(curr->cmd_path, curr->cmd_arr, data->exec_env) == -1)
			{
				set_exit_code(data, errno);
				print_err_exe(data, curr->cmd_arr[0], 2);
			}
		}
		else
		{
			set_exit_code(data, EACCES);
			print_err_exe(data, curr->cmd_arr[0], 2);
		}
	}
	else
	{
		set_exit_code(data, ENOENT);
		print_err_exe(data, curr->cmd_arr[0], 2);
	}
	clean_up_exec_creations(data, curr);
	mega_clean(data);
	return (FAIL);
}
