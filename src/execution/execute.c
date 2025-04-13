#include "../../inc/execution.h"

int		execute_cmd(t_struct_ptrs *data, t_input *input);
void	set_exit_code(t_struct_ptrs *data, int err);
int	launch_cmd_exec(t_struct_ptrs *data, t_input *curr, t_exec_data *exec_data);
void	run_in_child(t_struct_ptrs *data, t_input *curr, t_exec_data *exec_data);
void	check_if_cmd_is_path(t_input *curr);
void	make_cmd_path(t_struct_ptrs *data, t_input *curr);
void	turn_cmd_into_directory(t_struct_ptrs *data, t_input *curr, int i,
			char **tmp_cmd_path);
int		run_execve(t_struct_ptrs *data, t_input *curr);
void	wait_for_children(t_struct_ptrs *data);

void	execute(t_struct_ptrs *data)
{
	t_exec_data	exec_data;
	t_input	*curr;

	exec_data = (t_exec_data){0};
	exec_data.prev_read_end = -1;
	curr = data->input;

	if (!create_execute_env(data))
		return ; 
	if (split_env_path(data))
		return ;
	while (curr)
	{
		if (launch_cmd_exec(data, curr, &exec_data))
			break ; //how should this exit??
		curr = (t_input *)curr->base.next;
	}
	wait_for_children(data);
	return ;
	// }
	// should this return above or maybe clean up and then return? cause we dont want it to be overwritting stuff?
	// like the cmd.paths etc that I'll create later?
}

int	launch_cmd_exec(t_struct_ptrs *data, t_input *curr, t_exec_data *exec_data)
{
	int in_pipeline;

	if (curr->base.next)
		if (pipe(exec_data->pipe_fd) == -1)
			return (set_exit_code(data, -1), FAIL); // does this exit the whole mini or just this prompt?
	in_pipeline = curr->base.prev || curr->base.next;
	if (!is_builtin(curr) && !in_pipeline)
	{
		handle_standard_fds(exec_data, NO);
		if (set_std_fds(data, curr, exec_data))
			return (FAIL);
		launch_builtin(data, curr);
		handle_standard_fds(exec_data, YES);
	}
	else
	{
		exec_data->pid = fork();
		if (exec_data->pid == -1)
			return (set_exit_code(data, -1), FAIL);
		if (exec_data->pid == 0)
			run_in_child(data, curr, exec_data);
		else
		{
			if (exec_data->prev_read_end != -1)
				close_fd(&exec_data->prev_read_end);
			exec_data->prev_read_end = exec_data->pipe_fd[0];
			if (curr->base.next)
				close_fd(&exec_data->pipe_fd[1]);
		}
	}
	return (SUCCESS);
}

void	run_in_child(t_struct_ptrs *data, t_input *curr, t_exec_data *exec_data)
{
	if (exec_data->pid == 0) // child it will set the fd values, then close
	{
		if (set_std_fds(data, curr, exec_data))
			return;
		if (!is_builtin(curr))
		{
			launch_builtin(data, curr);
			exit (data->exit_code);
		}
		else if (execute_cmd(data, curr))
			exit(data->exit_code);
	}
}

int	execute_cmd(t_struct_ptrs *data, t_input *curr)
{
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
			}
		}
		else
		{
			set_exit_code(data, EACCES);
			print_err_exe(data, curr->cmd_arr[0], 2);
		}
	}
	else
	{
		set_exit_code(data, ENOENT);
		print_err_exe(data, curr->cmd_arr[0], 2);
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

void	wait_for_children(t_struct_ptrs *data)
{
	int	status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_code = 128 + WTERMSIG(status);
		pid = wait(&status);
	}
}