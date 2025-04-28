/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:17:53 by ydeng             #+#    #+#             */
/*   Updated: 2025/04/27 13:17:44 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expansion.h"

static char *handle_dollar_dollar(void);

char	*append_or_expand(char *src, int *i, char **new_str,
		t_struct_ptrs *data)
{
	char	*expand_value;
	char	*valid_variable;

	expand_value = NULL;
	valid_variable = NULL;
	if (src[*i] && should_just_append(src[*i], &src[*i]) == YES)
	{
		*new_str = append_character_in_string(*new_str, src[(*i)++]);
		if (!(*new_str))
			return (NULL);
		return (NULL);
	}
	else
	{
		valid_variable = chop_valid_variable(src, i);
		if (!valid_variable)
		{
			free(*new_str);
			*new_str = NULL;
			return (NULL);
		}
		expand_value = expand_valid_variable(valid_variable, data);
		return (expand_value);
	}
}

char	*chop_valid_variable(char *src, int *i)
{
	char	*valid_variable;
	int		j;

	j = 0;
	valid_variable = ft_calloc(ft_strlen(src), sizeof(char));
	if (!valid_variable)
		return (print_error("Malloc failure", NULL, NULL), NULL);
	(*i)++;
	if (src[*i] == '?' || src[*i] == '$')
	{
		valid_variable[j] = src[(*i)];
		(*i)++;
		j++;
	}
	else
		strcpy_to_valid_variable(src, &valid_variable, i, &j);
	valid_variable[j] = 0;
	valid_variable = append_character_in_string(valid_variable, '=');
	if (!valid_variable)
		return (NULL);
	return (valid_variable);
}

char	*expand_valid_variable(char *valid_variable, t_struct_ptrs *data)
{
	t_env_nodes	*temp;
	char		*ret;

	temp = data->env;
	ret = NULL;
	if (!ft_strncmp(valid_variable, "$=", 2))

		return (free(valid_variable), handle_dollar_dollar());
	if (!ft_strncmp(valid_variable, "?=", 2))
		return (free(valid_variable), handle_exit_code(data));
	else if (!get_var_value(temp, valid_variable))
		return (handle_non_valid_expansion(&valid_variable));
	else
	{
		ret = ft_strdup(get_var_value(temp, valid_variable));
		free_and_null(&valid_variable);
		if (ret)
			return (ret);
		return (print_error("Malloc failure", NULL, NULL), NULL);
	}
}

int	variable_init(int *i, char **new_str, char **expanded_value)
{
	*i = 0;
	*new_str = ft_strdup("");
	if (!new_str)
	{
		print_error("Malloc failure", NULL, NULL);
		return (FAIL);
	}
	*expanded_value = NULL;
	return (SUCCESS);
}

static char *handle_dollar_dollar(void)
{
	char 	*dollar;

	dollar = ft_strdup("$$");
	if (!dollar)
		return (NULL);
	return (dollar);
}
