/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:09:13 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/18 16:26:26 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

// int	if_redirection(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '<')
// 			return (INPUT);
// 		else if (str[i] == '>')
// 			return (OUTPUT);
// 		i++;
// 	}
// 	return (0);
// }





// void	handle_redir_sign(char *str, int index, t_token **head)
// {
// 	int		i;
// 	char	**split_words;

// 	i = 0;
// 	split_words = NULL;
// 	if (ft_strchr(str, '<'))
// 		split_words = ft_split(str, '<');
// 	if (!split_words)
// 		return ;
// 	while (split_words[i])
// 	{
// 		if (ft_strchr(split_words[i], ' '))
// 			trim_and_free(&split_words[i]);
// 		push_to_list(WORD, split_words[i], index, head);
// 		if (i == 0)
// 			push_to_list(INPUT, "<", index, head);
// 		i++;
// 	}
// 	free(split_words);
// 	split_words = NULL;
// }

// void	handle_normal(char *str, int index, t_token **head)
// {
// 	int		i;
// 	char	**split_words;

// 	i = 0;
// 	if (!ft_strchr(str, ' '))
// 	{
// 		printf("Error\n");
// 		return ;
// 	}
// 	split_words = ft_split(str, ' ');
// 	if (!split_words)
// 		return ;
// 	while (split_words[i])
// 	{
// 		if (ft_strchr(split_words[i], ' '))
// 			trim_and_free(&split_words[i]);
// 		push_to_list(WORD, split_words[i], index, head);
// 		i++;
// 	}
// 	free(split_words);
// 	split_words = NULL;
// }

// void	token_init(char *str, t_token **head)
// {
// 	int		i;
// 	int		index;
// 	char	**split_str;

// 	i = 0;
// 	index = 0;
// 	split_str = NULL;
// 	if (ft_strchr(str, '|'))
// 		split_str = find_pipe(str);
// 	else
// 		handle_redir_sign(str, index, head);
// 	while (split_str[i])
// 	{
// 		if (!ft_strchr(split_str[i], '<'))
// 			handle_normal(split_str[i], index, head);
// 		else
// 			handle_redir_sign(split_str[i], index, head);
// 		i++;
// 		index++;
// 	}
// }
