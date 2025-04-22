#include "../../inc/execution.h"

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
	if (data->split_path)
	{
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
	}
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
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_code = 128 + WTERMSIG(status);
			// data->exit_code = 0;
		pid = wait(&status);
	}
}
