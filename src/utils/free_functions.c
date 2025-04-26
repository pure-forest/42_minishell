/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:17:30 by ydeng             #+#    #+#             */
/*   Updated: 2025/04/26 17:17:31 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

void	free_lexer(t_token **head)
{
	t_token	*temp;

	if (!(*head))
		return ;
	while ((*head))
	{
		temp = (*head);
		(*head) = (t_token *)(*head)->base.next;
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		free(temp);
		temp = NULL;
	}
	return ;
}

void	free_redir(t_redir **head)
{
	t_redir	*temp;

	if (!(*head))
		return ;
	while ((*head))
	{
		temp = (*head);
		(*head) = (t_redir *)(*head)->base.next;
		if (temp->file_name)
		{
			free(temp->file_name);
			temp->file_name = NULL;
		}
		free(temp);
		temp = NULL;
	}
	return ;
}

void	free_cmd_table(t_input **head)
{
	t_input	*temp;

	if (!(*head))
		return ;
	while ((*head))
	{
		temp = (*head);
		*head = (t_input *)((*head)->base.next);
		if (temp->cmd_arr)
			ft_free_double_ptr(temp->cmd_arr);
		if (temp->redirection)
		{
			free_redir(&temp->redirection);
			free(temp->redirection);
			temp->redirection = NULL;
		}
		free(temp);
		temp = NULL;
	}
	return ;
}

void	ft_free_double_ptr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
		{
			free(str[i]);
			str[i] = NULL;
		}
		i++;
	}
	free(str);
	str = NULL;
}

void	free_and_null(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
		return ;
	}
	return ;
}
