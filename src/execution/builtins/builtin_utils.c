/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:28:35 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/29 11:46:28 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

int	is_equal_sign_present(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=')
			return (SUCCESS);
	}
	return (FAIL);
}

int	handle_shlvl(t_struct_ptrs *data, t_input *curr)
{
	if (curr->cmd_arr[1])
	{
		if (!ft_strncmp(curr->cmd_arr[1], "SHLVL=", 6))
		{
			if (!ft_strcmp(curr->cmd_arr[0], "unset")
				|| !ft_strcmp(curr->cmd_arr[0], "export"))
			{
				set_shell_level(data, "0");
				data->exit_code = SUCCESS;
				return (YES);
			}
		}
	}
	return (NO);
}
