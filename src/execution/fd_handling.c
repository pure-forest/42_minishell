#include "../../inc/execution.h"

void	close_pipe_fd(int *pipe_fd)
{
	if (pipe_fd[0] >= 0)
		close_fd(&pipe_fd[0]);
	if (pipe_fd[1] >= 0)
		close_fd(&pipe_fd[1]);
}
void	close_all_exec_fds(t_exec_data *exec_data)
{
	close_pipe_fd(exec_data->pipe_fd);
	close_fd(&exec_data->prev_read_end);
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
