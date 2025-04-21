#include "../../inc/execution.h"

void	close_pipe_fd(int *pipe_fd)
{
	if (pipe_fd[0] >= 0)
		close_fd(&pipe_fd[0]);
	if (pipe_fd[1] >= 0)
		close_fd(&pipe_fd[1]);
}

int check_inp_files(t_struct_ptrs *data, t_input *input, t_redir *redir_in, int *pipe_fd)
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

int	check_out_files(t_struct_ptrs *data, t_input *input, t_redir *redir_out, int *pipe_fd)
{
	if (input->output_fd >= 0)
		close_fd(&input->output_fd);
	if (redir_out->type == APPEND)
		input->output_fd = open(redir_out->file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		input->output_fd = open(redir_out->file_name, O_WRONLY | O_CREAT | O_TRUNC,
			0777);
	if (input->output_fd == -1)
	{
		set_exit_code(data, errno);
		close_pipe_fd(pipe_fd);
		return (print_err_exe(data, redir_out->file_name, 6), NO);
	}
	return (YES);
}

int	check_redir_files_for_exec(t_struct_ptrs *data, t_input *input, int *pipe_fd)
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
				// printf("After check_inp_files:\n");
				// system("ls -l /proc/self/fd");
			}
			else if (redir->type == OUTPUT || redir->type == APPEND)
			{
				if (!check_out_files(data, input, redir, pipe_fd))
					return (FAIL);
				// printf("After check_out_files:\n");
				// system("ls -l /proc/self/fd");
			}
			redir = (t_redir *)redir->base.next;
		}
	}
	return (SUCCESS);
}

int	set_std_fds(t_struct_ptrs *data, t_input *input, t_exec_data *exec_data)
{
	if (check_redir_files_for_exec(data, input, exec_data->pipe_fd))
		return (FAIL);
	if (input->input_fd != -1)
		dup2(input->input_fd, STDIN_FILENO);
	else if (input->base.prev && exec_data->prev_read_end != -1)
	{
		dup2(exec_data->prev_read_end, STDIN_FILENO);
		//close_fd(&exec_data->pipe_fd[0]);
		close_fd(&exec_data->prev_read_end);
	}
	if (input->output_fd >= 0)
	{
		if (input->output_fd != STDOUT_FILENO)
			dup2(input->output_fd, STDOUT_FILENO);
	}
	else if (input->base.next)
	{
		dup2(exec_data->pipe_fd[1], STDOUT_FILENO);
		close_fd(&exec_data->pipe_fd[1]);
	}
	return (SUCCESS);
}

void	handle_standard_fds(t_exec_data *exec_data, int reset)
{
	if (reset == NO)
	{
		exec_data->orig_stdin = dup(STDIN_FILENO);
		exec_data->orig_stdout = dup(STDOUT_FILENO);
	}
	if (reset == YES)
	{
		dup2(exec_data->orig_stdin, STDIN_FILENO);
		dup2(exec_data->orig_stdout, STDOUT_FILENO);
		close_fd(&exec_data->orig_stdin);
		close_fd(&exec_data->orig_stdout);
	}
	return ;
}
void	close_all_exec_fds(t_exec_data *exec_data)
{
	close_pipe_fd(exec_data->pipe_fd);
	close_fd(&exec_data->prev_read_end);
}