/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:30:20 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/28 11:38:40 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

void		prep_for_execve(t_struct_ptrs *data, t_input *curr);
static void	clean_up_and_exit(t_struct_ptrs *data, t_input *curr);

void	run_in_child(t_struct_ptrs *data, t_input *curr, t_exec_data *exec_data)
{
	if (check_redir_files_for_exec(data, curr, exec_data->pipe_fd))
		clean_up_and_exit(data, curr);
	if (set_std_fds(data, curr, exec_data))
		clean_up_and_exit(data, curr);
	close_all_exec_fds(exec_data);
	if (!curr->cmd_arr[0])
	{
		set_exit_code(data, SUCCESS);
		clean_up_and_exit(data, curr);
	}
	if (is_builtin(curr))
	{
		launch_builtin(data, curr, exec_data);
		clean_up_and_exit(data, curr);
	}
	else
		prep_for_execve(data, curr);
}

void	prep_for_execve(t_struct_ptrs *data, t_input *curr)
{
	check_if_cmd_is_path(curr);
	if (!curr->cmd_path)
	{
		make_cmd_path(data, curr);
		if (!curr->cmd_path)
		{
			set_exit_code(data, ENOENT);
			print_err_exe(data, curr->cmd_arr[0], 3);
			clean_up_and_exit(data, curr);
		}
	}
	if (curr->cmd_path)
		if (run_execve(data, curr))
			exit(data->exit_code);
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
			set_exit_code(data, errno);
			print_err_exe(data, curr->cmd_arr[0], 2);
		}
	}
	else
	{
		set_exit_code(data, errno);
		print_err_exe(data, curr->cmd_arr[0], 2);
	}
	clean_up_exec_creations(data, curr);
	mega_clean(data);
	return (FAIL);
}

static void	clean_up_and_exit(t_struct_ptrs *data, t_input *curr)
{
	clean_up_exec_creations(data, curr);
	mega_clean(data);
	exit (data->exit_code);
}

void	close_all_exec_fds(t_exec_data *exec_data)
{
	close_pipe_fd(exec_data->pipe_fd);
	close_fd(&exec_data->prev_read_end);
}
