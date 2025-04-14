#include "../../inc/execution.h"

int	get_err_code(int err)
{
	if (err == EACCES)
		return (126);
	if (err == ENOENT)
		return (127);
	return (1);
}

int	check_inp_files(t_struct_ptrs *data, t_input *input, char **redir_in,
		int *pipe_fd)
{
	int	i;

	i = -1;
	input->input_fd = -1;
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

int	check_out_files(t_struct_ptrs *data, t_input *input, char **redir_out,
		int *pipe_fd)
{
	int	i;

	i = -1;
	input->output_fd = -1;
	if (redir_out)
	{
		while (redir_out[++i])
		{
			if (input->append == YES && !redir_out[i + 1])
				input->output_fd = open(redir_out[i], O_WRONLY | O_CREAT | O_APPEND, 0777);
			else
				input->output_fd = open(redir_out[i], O_WRONLY | O_CREAT | O_TRUNC,
					0777);
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
	return (SUCCESS);
}

int	set_std_fds(t_struct_ptrs *data, t_input *input, t_exec_data *exec_data)
{
	if (check_inp_files(data, input, input->redir_in, exec_data->pipe_fd))
		return (FAIL);
	if (check_out_files(data, input, input->redir_out, exec_data->pipe_fd))
		return (FAIL);
	if (input->input_fd != -1)
		dup2(input->input_fd, STDIN_FILENO);
	else if (input->base.prev)
	{
		dup2(exec_data->prev_read_end, STDIN_FILENO);
		close_fd(&exec_data->pipe_fd[0]);
	}
	if (!input->base.next)
	{
		if (input->output_fd != -1 && input->output_fd != STDOUT_FILENO)
			dup2(input->output_fd, STDOUT_FILENO);
	}
	else
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
