#include "../../inc/execution.h"

// int		run_cmd_in_child(t_input *input, int prev_read_end);
int			run_cmd_in_child(t_struct_ptrs *data, t_input *input, int tmp);
void		set_exit_code(t_struct_ptrs *data, int err);
void		launch_command_exec(t_struct_ptrs *data);
int			set_std_fds(t_struct_ptrs *data, t_input *input, int *pipe_fd, int prev_read_end);

void	execute(t_struct_ptrs *data)
{
	if (!is_builtin(data)) // TODO --- this should be running in parent
	{
		data->exit_code = launch_builtin(data);
		return ;
	}
	else // TODO -- this should run in a child process
	{
		if (create_execute_env(data))
			return ; // do i need to set exit code?
		// int i = -1;		//TO BE DELETED
		// while (data->exec_env[++i])
		// printf("%s\n", data->exec_env[i]);
		launch_command_exec(data);
		// data->exit_code = run_in_child(data);
		return ;
	}
	// should this return above or maybe clean up and then return? cause we dont want it to be overwritting stuff?
	// like the cmd.paths etc that I'll create later?
}

void	launch_command_exec(t_struct_ptrs *data)
{
	int		pipe_fd[2];
	int		prev_read_end;
	int		pid;
	t_input	*curr;

	pipe_fd[0] = 0;
	pipe_fd[1] = 0;
	prev_read_end = -1;
	curr = data->input;
	while (curr)
	{
		if (curr->base.next)
			if (pipe(pipe_fd) == -1)
				return (set_exit_code(data, -1), (void)0);	// does this exit the whole mini or just this prompt?
		pid = fork();
		if (pid == -1)
			return (set_exit_code(data, -1), (void)0);
		if (pid == 0) // child it will set the fd values, then close
		{
			if (set_std_fds(data, curr, pipe_fd, prev_read_end))
				return ;
			close_fd(&pipe_fd[0]);
			close_fd(&pipe_fd[1]);
			// if (curr->base.next && !curr->base.prev)
			if (run_cmd_in_child(data, curr, 1))
					return ;
			// else
			// 	run_cmd_in_child(data, curr, 2);
		}
		else
		{
			if (prev_read_end != -1)
				close_fd(&prev_read_end);
			prev_read_end = pipe_fd[0];
			if (curr->base.next)
				close_fd(&pipe_fd[1]);
		}
		curr = (t_input *)curr->base.next;
	}
	close_fd(&pipe_fd[0]);
	close_fd(&pipe_fd[1]);
	// wait_for_children(&data);
	return ;
}

int	run_cmd_in_child(t_struct_ptrs *data, t_input *input, int tmp)
{
	(void)input;
	(void)data;
	if (tmp == 1)
		if (execve("/usr/bin/cat", input->cmd_arr, data->exec_env) == -1)
			return (FAIL);
	if (tmp == 2)
		execve("/usr/bin/grep", input->cmd_arr, data->exec_env);
	return (SUCCESS);
}
