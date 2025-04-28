/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:30:02 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/28 14:26:04 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			set_exit_code(data, SYS_FAIL);
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
			return (set_exit_code(data, SYS_FAIL), FAIL);
	in_pipeline = curr->base.prev || curr->base.next;
	if (is_builtin(curr) && !in_pipeline)
	{
		if (handle_standard_fds(data, exec_data, NO) == SYS_FAIL)
			return (FAIL);
		if (check_redir_files_for_exec(data, curr, exec_data->pipe_fd))
			return (close_opened_fd(curr), handle_standard_fds(data, exec_data, YES), FAIL);
		if (set_std_fds(data, curr, exec_data))
			return (close_opened_fd(curr), handle_standard_fds(data, exec_data, YES), FAIL);
		launch_builtin(data, curr, exec_data);
		close_opened_fd(curr);
		if (handle_standard_fds(data, exec_data, YES) == SYS_FAIL)
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
		return (set_exit_code(data, SYS_FAIL), FAIL);
	if (exec_data->pid == 0)
	{
		signal_init_child_process();
		run_in_child(data, curr, exec_data);
	}
	else
	{
		signal_init_parent_process();
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
	char	*new_value;
	int		i;

	i = -1;
	if (!curr->cmd_arr[0])
		new_value = "";
	else
	{
		while (curr->cmd_arr[++i])
			new_value = curr->cmd_arr[i];
	}
	last_cmd = get_var_value(data->env, "_=");
	if (!last_cmd)
		create_var_env_and_export(data, "_=", new_value);
	else
		update_var_in_both(data->env, data->export, "_=", new_value);
}
