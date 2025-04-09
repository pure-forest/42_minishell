#include "../../inc/execution.h"

int	check_inp_files(t_struct_ptrs *data, t_input *input, char **redir_in, int *pipe_fd)
{
	int	i;

	i = -1;
	if (redir_in)
	{
		while (redir_in[++i])
		{
			input->input_fd = open(redir_in[i], O_RDONLY, 0777);
			if (input->input_fd == -1)
			{
				set_exit_code(data, errno);
				close_fd(&pipe_fd[0]);
				close_fd(&pipe_fd[1]);
				return (print_err_exe(data, redir_in[i], 2), FAIL);
			}
			if (redir_in[i + 1])
				close_fd(&input->input_fd);
		}
	}
	return (SUCCESS);
}

int	check_out_files(t_struct_ptrs *data, t_input *input, char **redir_out, int *pipe_fd)
{
	int	i;

	i = -1;
	if (redir_out)
	{
		while (redir_out[++i])
		{
			input->output_fd = open(redir_out[i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (input->output_fd == -1)
			{
				set_exit_code(data, errno);
				close_fd(&pipe_fd[0]);
				close_fd(&pipe_fd[1]);
				return (print_err_exe(data, redir_out[i], 2), FAIL);
			}
			if (redir_out[i + 1])
				close_fd(&input->output_fd);
		}
	}
	input->output_fd = STDOUT_FILENO;
	return (SUCCESS);
}

int	set_std_fds(t_struct_ptrs *data, t_input *input, int *pipe_fd, int prev_read_end)
{
	if (check_inp_files(data, input, input->redir_in, pipe_fd))
		return (FAIL);
	if (check_out_files(data, input, input->redir_out, pipe_fd))
		return (FAIL);
	if (!input->base.prev)
		if (input->input_fd)
			dup2(input->input_fd, STDIN_FILENO);
	if (input->base.prev)
		dup2(prev_read_end, STDIN_FILENO);
	if (!input->base.next)
		if (input->output_fd && input->output_fd != STDOUT_FILENO)
			dup2(input->output_fd, STDOUT_FILENO);
	if (input->base.next)
		dup2(pipe_fd[1], STDOUT_FILENO);
	// close_fd(&pipe_fd[0]);
	// close_fd(&pipe_fd[1]);
	return (SUCCESS);
}
