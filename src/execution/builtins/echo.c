/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:27:56 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/26 17:27:57 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

static int	check_arg(char *arg);

int	echo(t_input *curr)
{
	int		i;
	char	**cmd_arr;
	int		flag;

	i = 1;
	flag = 0;
	cmd_arr = curr->cmd_arr;
	while (cmd_arr[i] && !check_arg(cmd_arr[i]))
	{
		flag = 1;
		i++;
	}
	while (cmd_arr[i])
	{
		printf("%s", cmd_arr[i]);
		if (cmd_arr[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (SUCCESS);
}

static int	check_arg(char *arg)
{
	while (*arg)
	{
		if (*arg == '-')
		{
			arg++;
			if (*arg == 'n')
			{
				while (*arg == 'n')
					arg++;
				if (*arg)
					return (FAIL);
				return (SUCCESS);
			}
			return (FAIL);
		}
		arg++;
	}
	return (FAIL);
}
