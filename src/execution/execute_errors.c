/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:29:54 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/26 17:29:55 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

void	print_err_exe(t_struct_ptrs *data, char *cmd, int err)
{
	if (err == 1)
		perror(PROMPT);
	if (err == 2 || err == 3 || err == 4 || err == 6)
	{
		if (data->exit_code == 126 && err != 4)
			print_error(cmd, NULL, ": Permission denied");
		else if ((data->exit_code == 127 && err == 2) || (data->exit_code == 126
				&& err == 4) || (data->exit_code == -1) || err == 6)
			print_error(cmd, NULL, ": No such file or directory");
		else if (data->exit_code == 127 && err == 3)
			print_error(cmd, NULL, ": command not found");
	}
	if (err == 6)
		data->exit_code = 1;
}

void	print_error(char *var, char *var_2, char *str)
{
	ft_putstr_fd("catshell: ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(var_2, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	close_fd(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

int	get_errno_codes(int err)
{
	if (err == SUCCESS)
		return (0);
	if (err == ENOENT)
		return (127);
	if (err == EACCES)
		return (126);
	if (err == SYS_FAIL)
		return (-1);
	if (err == 4)
		return (2);
	return (1);
}

void	set_exit_code(t_struct_ptrs *data, int err)
{
	data->exit_code = get_errno_codes(err);
}
