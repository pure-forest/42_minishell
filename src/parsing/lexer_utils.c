/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:25:42 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/18 13:22:47 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	print_token_list(t_token *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		// printf("lexer->type = %d index = %d lexer->value = %s\n",
		// 	lexer->type, lexer->pipe_index, lexer->value);
		printf("index:%d   %s[type: %d] \n", lexer->pipe_index, lexer->value, lexer->type);
		printf("vvv\n");
		lexer = lexer->next;
		i++;
	}
	// printf("%s[%d] next>> \n", lexer->value, lexer->type);
	// while (lexer)
	// {
	// 	printf("=prev>> %s[%d] ", lexer->value, lexer->type);
	// 	lexer = lexer->prev;
	// }
	printf("\n-------------end of lexer-----------\n\n");
}

void	free_lexer(t_token **head)
{
	t_token	*temp;
	int		i;

	i = 1;
	if (!(*head))
		return ;
	while ((*head))
	{
		temp = (*head);
		*head = (*head)->next;
		if (temp->type == WORD && temp->value)
			free(temp->value);
		free(temp);
		temp = NULL;
	}
	return ;
}
