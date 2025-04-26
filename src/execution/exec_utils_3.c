/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:29:14 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/26 17:29:15 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	check_if_cmd_is_path(t_input *curr)
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
				return (YES);
			}
		}
	}
	return (NO);
}

void	make_cmd_path(t_struct_ptrs *data, t_input *curr)
{
	int		i;
	char	*tmp_cmd_path;

	i = -1;
	if (data->split_path)
	{
		if (!ft_strcmp(curr->cmd_arr[0], ""))
			return ;
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
		pid = wait(&status);
	}
	if (data->exit_code == 131)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (data->exit_code == 130)
		printf("\n");
}

void	init_exec_data(t_exec_data *exec_data)
{
	*exec_data = (t_exec_data){0};
	exec_data->prev_read_end = -1;
	exec_data->pipe_fd[0] = -1;
	exec_data->pipe_fd[1] = -1;
	return ;
}
