/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:39:12 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/19 12:39:12 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	append_node(t_list_base *list_to_modify, t_list_base *new_var)
{
	t_list_base	*last_var;

	last_var = find_last(list_to_modify);
	if (!last_var)
		return (FAIL);
	last_var->next = new_var;
	new_var->prev = last_var;
	return (SUCCESS);
}

t_list_base	*find_last(t_list_base *root)
{
	if (!root)
		return (NULL);
	while (root->next)
		root = root->next;
	return (root);
}
