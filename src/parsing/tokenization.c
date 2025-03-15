/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:09:13 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/15 17:28:42 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"
#include <string.h>

void	print_list(t_token *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		printf("[%d] lexer->type = %d index = %d lexer->value = %s\n", i,
			lexer->type, lexer->pipe_index, lexer->value);
		lexer = lexer->next;
		i++;
	}
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
	(*head) = temp;
}

void	token_input(char *str, t_token **head)
{
	int		i;
	int		index;
	char	**trimed_str;

	i = 0;
	index = 0;
	trimed_str = ft_split(str, ' ');
	while (trimed_str[i])
	{
		if (ft_strnstr(trimed_str[i], "|", 1))
			push_to_list(PIPE, "|", index++, head);
		else if (ft_strnstr(trimed_str[i], "<<", 2))
			push_to_list(HEREDOC, "<<", index, head);
		else if (ft_strnstr(trimed_str[i], ">", 1))
			push_to_list(INPUT, ">", index, head);
		else if (ft_strnstr(trimed_str[i], "<", 1))
			push_to_list(OUTPUT, "<", index, head);
		else
			push_to_list(WORD, trimed_str[i], index, head);
		i++;
	}
}
