/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:09:13 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/20 20:29:08 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	push_to_list(t_token_type num, char *value, t_token **head)
{
	t_token	*temp;

	temp = malloc(sizeof(t_token));
	if (!temp)
	{
		return ;
	}
	temp->type = num;
	temp->value = value;
	temp->next = (*head);
	if (*head)
		(*head)->prev = temp;
	(*head) = temp;
	(*head)->prev = NULL;
}

void	print_double_ptr(char **str)
{
	int	i = 0;

	while (str[i])
	{
		printf("str[%d] = %s\n", i, str[i]);
		i++;
	}
}

char	*extract_input(char *needle)
{
	int		i = 0;
	char	*end;
	char	*return_str;

	while (needle[i])
	{
		if (needle[i] == ' ' || needle[i] == '|')
			end = &needle[i];
		i++;
	}
	return_str = ft_substr(needle + 1, 0, end - needle - 1);
	return (return_str);
}

void	token_init(char *str, t_token **head)
{
	char	*infile = NULL;
	int		i = 0;

	if (ft_strchr(str, '<') && *ft_strchr(str, '<') + 1 != ' ')
	{
		infile = extract_input(ft_strchr(str, '<'));
		printf("%s", infile);
		push_to_list(INPUT, "<", head);
		push_to_list(INFILE, infile, head);
	}
	while (str[i])
	{
		if ()
	}

}
