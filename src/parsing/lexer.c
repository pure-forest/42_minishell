/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:09:13 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/16 17:02:24 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	print_token_list(t_token *lexer)
{
	int	i;

	i = 0;
	while (lexer->next)
	{
		// printf("lexer->type = %d index = %d lexer->value = %s\n",
		// 	lexer->type, lexer->pipe_index, lexer->value);
		printf("%s[%d] =next>> ", lexer->value, lexer->type);
		lexer = lexer->next;
		i++;
	}
	printf("%s[%d] =next>> \n", lexer->value, lexer->type);
	while (lexer)
	{
		printf("=prev>> %s[%d] ", lexer->value, lexer->type);
		lexer = lexer->prev;
	}
	printf("\n---end of lexer-----\n");
}

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

void	free_lexer(t_token **head)
{
	t_token *temp;

	temp = (*head);
	while (temp)
	{
		free(temp);
		temp = NULL;
		temp = (*head)->next;
	}
	return ;
}

void	token_init(char *str, t_token **head)
{
	int		i;
	int		index;
	char	**trimed_str;

	i = 0;
	index = 0;
	if ((*head))
		free_lexer(head);
	trimed_str = ft_split(str, ' ');
	while (trimed_str[i])
	{
		if (ft_strnstr(trimed_str[i], "|", 1))
			push_to_list(PIPE, "|", index++, head);
		else if (ft_strnstr(trimed_str[i], "<<", 2))
			push_to_list(HEREDOC, "<<", index, head);
		else if (ft_strnstr(trimed_str[i], ">", 1))
			push_to_list(OUTPUT, ">", index, head);
		else if (ft_strnstr(trimed_str[i], "<", 1))
			push_to_list(INPUT, "<", index, head);
		else
			push_to_list(WORD, trimed_str[i], index, head);
		i++;
	}
}
