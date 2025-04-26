/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:16:21 by ydeng             #+#    #+#             */
/*   Updated: 2025/04/26 17:16:22 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static char	*valid_variable_init(t_token **node, int *i);

char	*check_quote_expansion(t_struct_ptrs *data, t_token **node, int *i,
		int *j)
{
	char	*ret;
	char	*valid_variable;

	valid_variable = valid_variable_init(node, i);
	ret = expand_variable(data, valid_variable);
	if (!ret)
	{
		free_and_null(&ret);
		free_and_null(&valid_variable);
		(*j)++;
	}
	else if (!*ret)
	{
		free_and_null(&ret);
		(*j)++;
	}
	else
		(*j) += ft_strlen(ret);
	(*node)->should_expand = NO;
	return (ret);
}

static char	*valid_variable_init(t_token **node, int *i)
{
	int		length;
	char	*valid_variable;

	length = 0;
	valid_variable = NULL;
	while ((!ft_strchr("\'\"", (*node)->value[*i])) && (*node)->value[*i])
	{
		(*i)++;
		length++;
	}
	valid_variable = ft_strndup(&((*node)->value)[*i - length], length);
	if (!valid_variable)
		return (NULL);
	return (valid_variable);
}
