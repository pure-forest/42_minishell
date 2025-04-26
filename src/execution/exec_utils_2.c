/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:29:09 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/26 17:29:10 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	check_inp_files(t_struct_ptrs *data, t_input *input, t_redir *redir_in,
		int *pipe_fd)
{
	if (input->input_fd >= 0)
		close_fd(&input->input_fd);
	input->input_fd = open(redir_in->file_name, O_RDONLY, 0777);
	if (input->input_fd == -1)
	{
		set_exit_code(data, errno);
		close_pipe_fd(pipe_fd);
		return (print_err_exe(data, redir_in->file_name, 6), NO);
	}
	return (YES);
}

int	check_out_files(t_struct_ptrs *data, t_input *input, t_redir *redir_out,
		int *pipe_fd)
{
	if (input->output_fd >= 0)
		close_fd(&input->output_fd);
	if (redir_out->type == APPEND)
		input->output_fd = open(redir_out->file_name,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		input->output_fd = open(redir_out->file_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (input->output_fd == -1)
	{
		set_exit_code(data, errno);
		close_pipe_fd(pipe_fd);
		return (print_err_exe(data, redir_out->file_name, 6), NO);
	}
	return (YES);
}

int	check_redir_files_for_exec(t_struct_ptrs *data, t_input *input,
		int *pipe_fd)
{
	t_redir	*redir;

	input->input_fd = -1;
	input->output_fd = -1;
	redir = input->redirection;
	if (redir)
	{
		while (redir)
		{
			if (redir->type == INPUT)
			{
				if (!check_inp_files(data, input, redir, pipe_fd))
					return (FAIL);
			}
			else if (redir->type == OUTPUT || redir->type == APPEND)
			{
				if (!check_out_files(data, input, redir, pipe_fd))
					return (FAIL);
			}
			redir = (t_redir *)redir->base.next;
		}
	}
	return (SUCCESS);
}
