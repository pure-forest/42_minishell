/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:26:44 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/18 16:57:42 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	push_to_list(t_token_type num, char *value, int index, t_token **head)
{
	t_token	*temp;

	temp = malloc(sizeof(t_token));
	if (!temp)
	{
		return ;
	}
	temp->type = num;
	temp->pipe_index = index;
	temp->value = value;
	temp->next = (*head);
	if (*head)
		(*head)->prev = temp;
	(*head) = temp;
	(*head)->prev = NULL;
}

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
