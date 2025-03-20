/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:26:44 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/20 16:04:39 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	free_cmd_table(t_cmd_table **head)
{
	t_cmd_table	*temp;
	int			i;

	i = 1;
	if (!(*head))
		return ;
	while ((*head))
	{
		temp = (*head);
		*head = (*head)->next;
		if (temp->cmd_args)
			ft_free_double_ptr(temp->cmd_args);
		if (temp->cmd)
		{
			free(temp->cmd);
			temp->cmd = NULL;
		}
		free(temp);
		temp = NULL;
	}
	return ;
}
