#include "../../inc/execution.h"

int		run_cmd_in_child(t_struct_ptrs *data);
void	set_exit_code(t_struct_ptrs *data, int err);

void	execute(t_struct_ptrs *data)
{
	if (!is_builtin(data))	//TODO --- this should be running in parent
	{
		data->exit_code = launch_builtin(data);
		return ;
	}
	else	//TODO -- this should run in a child process
	{
		if (create_execute_env(data))
			return ;	// do i need to set exit code?
		int i = -1;		//TO BE DELETED
		while (data->exec_env[++i])
		printf("%s\n", data->exec_env[i]);

		launch_command_exec(data);
		//data->exit_code = run_in_child(data);
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

	prev_read_end = -1;
	curr = data->input;
	while (curr)
	{
		if (curr->base.next)
			if (pipe(pipe_fd) == -1)
				return (set_exit_code(data, -1), (void)0); //does this exit the whole mini or just this prompt?
		pid = fork();
		if (pid == -1)
			return (set_exit_code(data, -1), (void)0);
		if (pid == 0)
		{
			set_std_fds(curr);
			close(pipe_fd[0]);
			run_cmd_in_child(curr);
		}
		else
		{
			close(pipe_fd[1]);
			prev_read_end = pipe_fd[0];
		}
		curr = curr->base.next;
	}
	close(pipe_fd[0]);
	wait_for_children(&data);
	return ;
}

int	run_cmd_in_child(t_input *input)
{
	if (check_files(data))
		return (FAIL);
	return (SUCCESS);
}

void	set_exit_code(t_struct_ptrs *data, int err)
{
	data->exit_code = get_errno_codes(err);
}