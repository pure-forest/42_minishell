/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:17:49 by ydeng             #+#    #+#             */
/*   Updated: 2025/04/26 17:17:50 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expansion.h"

bool	is_valid_expandable(char c)
{
	if (c == 0)
		return (NO);
	if (ft_isalnum(c) || ft_isalpha(c) || c == '_')
		return (YES);
	else
		return (NO);
}

bool	should_just_append(char c, char *src)
{
	int	i;

	i = 0;
	if (c == '$' && (src[i + 1] == '?' || src[i + 1] == '$'))
		return (NO);
	else if (c == '$' && is_valid_expandable(src[i + 1]) == NO)
		return (YES);
	else if (c != '$')
		return (YES);
	else
		return (NO);
}

char	*handle_exit_code(t_struct_ptrs *data)
{
	char	*exit_code;

	exit_code = ft_itoa(data->exit_code);
	if (!exit_code)
		return (print_error("Malloc failure", NULL, NULL), NULL);
	return (exit_code);
}

void	strcpy_to_valid_variable(char *src, char **valid_variable, int *i,
		int *j)
{
	while (is_valid_expandable(src[*i]) == YES)
	{
		(*valid_variable)[*j] = src[(*i)];
		(*j)++;
		(*i)++;
	}
}

char	*handle_non_valid_expansion(char **valid_variable)
{
	char	*empty_string;

	free(*valid_variable);
	*valid_variable = NULL;
	empty_string = ft_strdup("");
	if (!empty_string)
		return (print_error("Malloc failure", NULL, NULL), NULL);
	return (empty_string);
}
