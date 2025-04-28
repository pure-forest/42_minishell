/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:30:07 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/28 15:16:35 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

void	close_pipe_fd(int *pipe_fd)
{
	if (pipe_fd[0] >= 0)
		close_fd(&pipe_fd[0]);
	if (pipe_fd[1] >= 0)
		close_fd(&pipe_fd[1]);
}

void	close_opened_fd(t_input *curr)
{
	if (curr)
	{
		if (curr->input_fd >= 0)
			close_fd(&curr->input_fd);
		if (curr->output_fd >= 0)
			close_fd(&curr->output_fd);
	}
}

int	set_std_fds(t_struct_ptrs *data, t_input *input, t_exec_data *exec_data)
{
	if (input->input_fd != -1)
	{
		if (dup2(input->input_fd, STDIN_FILENO) == -1)
			return (handle_fd_err(data, exec_data, "Dup2 Failure"), FAIL);
	}
	else if (input->base.prev && exec_data->prev_read_end != -1)
	{
		if (dup2(exec_data->prev_read_end, STDIN_FILENO) == -1)
			return (handle_fd_err(data, exec_data, "Dup2 Failure"), FAIL);
		close_fd(&exec_data->prev_read_end);
	}
	if (input->output_fd >= 0)
	{
		if (input->output_fd != STDOUT_FILENO)
			if (dup2(input->output_fd, STDOUT_FILENO) == -1)
				return (handle_fd_err(data, exec_data, "Dup2 Fail"), FAIL);
	}
	else if (input->base.next)
	{
		if (dup2(exec_data->pipe_fd[1], STDOUT_FILENO) == -1)
			return (handle_fd_err(data, exec_data, "Dup2 Fail"), FAIL);
		close_fd(&exec_data->pipe_fd[1]);
	}
	return (SUCCESS);
}

int	handle_standard_fds(t_struct_ptrs *data, t_exec_data *exec_data, int reset)
{
	int	res;

	if (reset == NO)
	{
		exec_data->orig_stdin = dup(STDIN_FILENO);
		if (exec_data->orig_stdin == -1)
			return (handle_fd_err(data, exec_data, "Dup Fail"), SYS_FAIL);
		exec_data->orig_stdout = dup(STDOUT_FILENO);
		if (exec_data->orig_stdout == -1)
			return (handle_fd_err(data, exec_data, "Dup Fail"), SYS_FAIL);
	}
	if (reset == YES)
	{
		res = dup2(exec_data->orig_stdin, STDIN_FILENO);
		if (res == -1)
			return (handle_fd_err(data, exec_data, "Dup2 Fail"), SYS_FAIL);
		res = dup2(exec_data->orig_stdout, STDOUT_FILENO);
		if (res == -1)
			return (handle_fd_err(data, exec_data, "Dup2 Fail"), SYS_FAIL);
		close_fd(&exec_data->orig_stdin);
		close_fd(&exec_data->orig_stdout);
	}
	return (SUCCESS);
}

void	handle_fd_err(t_struct_ptrs *data, t_exec_data *exec_data,
		char *err_msg)
{
	print_error(err_msg, NULL, NULL);
	set_exit_code(data, SYS_FAIL);
	if (exec_data->orig_stdin >= 0)
		close_fd(&exec_data->orig_stdin);
	if (exec_data->orig_stdout >= 0)
		close_fd(&exec_data->orig_stdout);
	if (exec_data->prev_read_end >= 0)
		close_fd(&exec_data->prev_read_end);
	close_pipe_fd(exec_data->pipe_fd);
}
