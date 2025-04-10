#include "../../inc/execution.h"

// int		run_cmd_in_child(t_input *input, int prev_read_end);
int		run_cmd_in_child(t_struct_ptrs *data, t_input *input);
void	set_exit_code(t_struct_ptrs *data, int err);
// void		launch_command_exec(t_struct_ptrs *data);
void	launch_command_exec(t_struct_ptrs *data, int *pipe_fd, int pid,
			int prev_read_end);
int		set_std_fds(t_struct_ptrs *data, t_input *input, int *pipe_fd,
			int prev_read_end);
void	check_if_cmd_is_path(t_input *curr);
void	make_cmd_path(t_struct_ptrs *data, t_input *curr);
void	turn_cmd_into_directory(t_struct_ptrs *data, t_input *curr, int i,
			char **tmp_cmd_path);
int		run_execve(t_struct_ptrs *data, t_input *curr);

// for (int fd = 0; fd < 10; fd++)
// if (fcntl(fd, F_GETFD) != -1)
// 	printf("Run_cmd:	FD %d is open\n", fd);

void	execute(t_struct_ptrs *data)
{
	int	pipe_fd[2];
	int	prev_read_end;
	int	pid;

	pipe_fd[0] = 0;
	pipe_fd[1] = 0;
	prev_read_end = -1;
	pid = 0;
	// if (!is_builtin(data)) // TODO --- this should be running in parent
	// {
	// 	data->exit_code = launch_builtin(data);
	// 	return ;
	// }
	// else // TODO -- this should run in a child process
	// {
	if (create_execute_env(data))
		return ; // do i need to set exit code?
				// int i = -1;		//TO BE DELETED
				// while (data->exec_env[++i])
				// printf("%s\n", data->exec_env[i]);
	if (split_env_path(data))
		return ;
	// int i = -1;
	// while (data->split_path[++i])
	// 	printf("[%d]: %s\n", i, data->split_path[i]);
	launch_command_exec(data, pipe_fd, pid, prev_read_end);
	// wait_for_children(data);
	return ;
	// }
	// should this return above or maybe clean up and then return? cause we dont want it to be overwritting stuff?
	// like the cmd.paths etc that I'll create later?
}

void	launch_command_exec(t_struct_ptrs *data, int *pipe_fd, int pid,
		int prev_read_end)
{
	t_input	*curr;
	int		in_pipeline;

	curr = data->input;
	while (curr)
	{
		if (curr->base.next)
			if (pipe(pipe_fd) == -1)
				return (set_exit_code(data, -1), (void)0);
		// does this exit the whole mini or just this prompt?
		in_pipeline = curr->base.prev || curr->base.next;
		if (!is_builtin(data) && !in_pipeline)
		{
			if (set_std_fds(data, curr, pipe_fd, prev_read_end))
				return ;
			launch_builtin(data, curr);
		}
		else
		{
			pid = fork();
			if (pid == -1)
				return (set_exit_code(data, -1), (void)0);
			if (pid == 0) // child it will set the fd values, then close
			{
				if (set_std_fds(data, curr, pipe_fd, prev_read_end))
					return ;
				if (!is_builtin(data))
					launch_builtin(data, curr);
				else
					if (run_cmd_in_child(data, curr))
				exit (data->exit_code);
			}
			else
			{
				if (prev_read_end != -1)
					close_fd(&prev_read_end);
				prev_read_end = pipe_fd[0];
				if (curr->base.next)
					close_fd(&pipe_fd[1]);
			}
		}
		curr = (t_input *)curr->base.next;
	}
	// wait_for_children(&data);
	return ;
}

int	run_cmd_in_child(t_struct_ptrs *data, t_input *curr)
{
	(void)data;
	(void)curr;
	check_if_cmd_is_path(curr);
	if (!curr->cmd_path)
	{
		make_cmd_path(data, curr);
		if (!curr->cmd_path)
		{
			set_exit_code(data, ENOENT);
			print_err_exe(data, curr->cmd_arr[0], 3);
			return (FAIL);
		}
	}
	if (curr->cmd_path)
		if (run_execve(data, curr))
			return (FAIL);
	return (SUCCESS);
}

int	run_execve(t_struct_ptrs *data, t_input *curr)
{
	if (access(curr->cmd_path, F_OK) == 0)
	{
		if (access(curr->cmd_path, X_OK) == 0)
		{
			if (execve(curr->cmd_path, curr->cmd_arr, data->split_path) == -1)
			{
				set_exit_code(data, errno);
				print_err_exe(data, curr->cmd_arr[0], 2);
				// return (FAIL);
			}
		}
		else
		{
			set_exit_code(data, EACCES);
			print_err_exe(data, curr->cmd_arr[0], 2);
			// return (FAIL);
		}
	}
	else
	{
		set_exit_code(data, ENOENT);
		print_err_exe(data, curr->cmd_arr[0], 2);
		// return (FAIL);
	}
	return (FAIL);
}

void	check_if_cmd_is_path(t_input *curr)
{
	int	i;

	i = -1;
	if (curr->cmd_arr[0])
	{
		while (curr->cmd_arr[0][++i])
		{
			if (curr->cmd_arr[0][i] == '/')
			{
				curr->cmd_path = curr->cmd_arr[0];
				return ;
			}
		}
	}
}

// right now i have the path split, i have to check every path for the cmd
// and to do that the cmd has to be in directory format /usr/bin/cat
void	make_cmd_path(t_struct_ptrs *data, t_input *curr)
{
	int		i;
	char	*tmp_cmd_path;

	i = -1;
	while (data->split_path[++i])
	{
		turn_cmd_into_directory(data, curr, i, &tmp_cmd_path);
		if (!tmp_cmd_path)
			return ;
		if (access(tmp_cmd_path, F_OK | X_OK) == 0)
		{
			curr->cmd_path = tmp_cmd_path;
			return ;
		}
		free(tmp_cmd_path);
		tmp_cmd_path = NULL;
	}
	curr->cmd_path = NULL;
	return ;
}

void	turn_cmd_into_directory(t_struct_ptrs *data, t_input *curr, int i,
		char **tmp_cmd_path)
{
	char	*tmp;

	tmp = ft_strjoin(data->split_path[i], "/");
	if (!tmp)
	{
		tmp_cmd_path = NULL;
		return ;
	}
	*tmp_cmd_path = ft_strjoin(tmp, curr->cmd_arr[0]);
	free(tmp);
	return ;
}
