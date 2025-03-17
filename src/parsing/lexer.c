/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:09:13 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/17 15:39:50 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int	if_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
			return (INPUT);
		else if (str[i] == '>')
			return (OUTPUT);
		i++;
	}
	return (0);
}

void	trim_and_free(char **src)
{
	char	*temp;

	temp = ft_strtrim((*src), " ");
	if (!temp)
	{
		free(*src);
		*src = NULL;
		return ;
	}
	free(*src);
	*src = temp;
}

void	handle_input_sign(char *str, int index, t_token **head)
{
	int		i;
	char	**split_words;

	i = 0;
	split_words = ft_split(str, '<');
	while (split_words[i])
	{
		if (ft_strchr(split_words[i], ' '))
			trim_and_free(&split_words[i]);
		push_to_list(WORD, split_words[i], index, head);
		if (i == 0)
			push_to_list(INPUT, "<", index, head);
		i++;
	}
	free(split_words);
	split_words = NULL;
}

void	token_init(char *str, t_token **head)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	if (if_redirection(str) == INPUT)
		handle_input_sign(str, index, head);
}
