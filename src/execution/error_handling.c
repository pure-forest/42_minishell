/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:30:58 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/14 00:30:58 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

void	error_handling(t_struct_ptrs *data)
{
	if (data->env)
		free_env_nodes(&data->env);
}

void	free_env_nodes(t_env_nodes **root)
{
	t_env_nodes	*tmp;
	t_env_nodes	*curr;

	if (!root || !*root)
		return ;
	curr = *root;
	while (curr)
	{
		tmp = (t_env_nodes *)curr->base.next;
		free(curr->var_name);
		free(curr->var_value);
		free(curr);
		curr = tmp;
	}
	*root = NULL;
}
