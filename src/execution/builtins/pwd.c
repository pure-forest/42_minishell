/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:04:10 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/16 19:25:12 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

int	pwd(t_struct_ptrs *data)
{
	t_env_nodes   *curr;

	curr = NULL;
	if (data->env)
	{
		curr = data->env;
		while (curr && (curr = curr->next))
		{
			if (!(ft_strncmp(curr->str, "PWD=", 4)))
				return(printf("%s\n", (curr->str + 4)), 0);
		}
		return (1);
	}
	return (1);
}