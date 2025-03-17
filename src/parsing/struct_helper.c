/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:26:44 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/17 15:26:57 by ydeng            ###   ########.fr       */
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


