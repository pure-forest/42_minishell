/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:04:10 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/20 15:20:13 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

int	pwd(t_struct_ptrs *data)
{
	t_env_nodes	*curr;

	curr = NULL;
	if (data->env)
	{
		curr = data->env;
		while (curr)
		{
			if (!(ft_strncmp(curr->var_name, "PWD=", 4)))
				return (printf("%s\n", curr->var_value), 0);
			curr = (t_env_nodes *)curr->base.next;
		}
		return (1);
	}
	return (1);
}
