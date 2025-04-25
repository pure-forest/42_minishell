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
				return (handle_fd_err(data, exec_data, "Dup2 Failure"), FAIL);
	}
	else if (input->base.next)
	{
		if (dup2(exec_data->pipe_fd[1], STDOUT_FILENO) == -1)
			return (handle_fd_err(data, exec_data, "Dup2 Failure"), FAIL);
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
			return (handle_fd_err(data, exec_data, "Dup Failed"), SYSTEM_FAIL);
		exec_data->orig_stdout = dup(STDOUT_FILENO);
		if (exec_data->orig_stdout == -1)
			return (handle_fd_err(data, exec_data, "Dup Failed"), SYSTEM_FAIL);
	}
	if (reset == YES)
	{
		res = dup2(exec_data->orig_stdin, STDIN_FILENO);
		if (res == -1)
			return (handle_fd_err(data, exec_data, "Dup2 Failed"), SYSTEM_FAIL);
		res = dup2(exec_data->orig_stdout, STDOUT_FILENO);
		if (res == -1)
			return (handle_fd_err(data, exec_data, "Dup2 Failed"), SYSTEM_FAIL);
		close_fd(&exec_data->orig_stdin);
		close_fd(&exec_data->orig_stdout);
	}
	return (SUCCESS);
}

void	handle_fd_err(t_struct_ptrs *data, t_exec_data *exec_data,
			char *err_msg)
{
	print_error(err_msg, NULL, NULL);
	set_exit_code(data, SYSTEM_FAIL);
	if (exec_data->orig_stdin)
		close_fd(&exec_data->orig_stdin);
	if (exec_data->orig_stdout)
		close_fd(&exec_data->orig_stdout);
	if (exec_data->prev_read_end)
		close_fd(&exec_data->prev_read_end);
	close_pipe_fd(exec_data->pipe_fd);
}
