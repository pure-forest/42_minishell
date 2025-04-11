#include "../../inc/expansion.h"

static char	*chop_valid_variable(char *src, int *i, t_struct_ptrs *data);
static bool is_valid_expandable(char c);

int	expand_word_token(t_struct_ptrs *data)
{
	t_token *node;

	node = data->token;
	while (node)
	{
		if (node->should_expand == YES && ft_strchr(node->value, '$'))
		{
			(node)->expanded_value = expand_variable(data, node->value);
			if (!(node)->expanded_value)
				return (FAIL);
			// if (!*new_value)
			// {
				// free(new_value);
				// new_value = NULL;
			// 	return (SUCCESS);
			// }
			node->value = (node)->expanded_value;
		}
		node = (t_token *)(node->base.next);
	}
	return (SUCCESS);
}

char	*expand_variable(t_struct_ptrs *data, char *src)
{
	char	*new_str;
	char	*expanded_value;
	int		i;

	if (!src || !*src)
		return (NULL);
	i = 0;
	new_str = ft_strdup("");
	expanded_value = NULL;
	while (src[i])
	{
		if (expanded_value == NULL)
		{
			if (src[i] != '$')
				new_str = append_character_in_string(new_str, src[i++]);
			else
				expanded_value = chop_valid_variable(&src[i], &i, data);
		}
		else
		{
			new_str = ft_strjoin_and_free(new_str, expanded_value);
			expanded_value = NULL;
		}
	}
	return (new_str);
}

static char	*chop_valid_variable(char *src, int *i, t_struct_ptrs *data)
{
	char	*valid_variable;
	char	*ret;
	int	j;

	j = 0;
	valid_variable = ft_calloc(ft_strlen(src), sizeof(char));
	(*i)++;
	while (is_valid_expandable(src[*i]) == YES)
	{
		valid_variable[j] = src[(*i)];
		j++;
		(*i)++;
	}
	valid_variable[j] = 0;
	valid_variable = append_character_in_string(valid_variable, '=');
	if (!ft_strncmp(valid_variable, "$=", 2))
		return (free(valid_variable), ft_itoa(getpid()));
	else
		ret = get_var_value(data->env, valid_variable);
	free(valid_variable);
	if (!ret)
		return (ft_strdup(""));
	else
		return (ret);
}

static bool is_valid_expandable(char c)
{
	if (c == 0)
		return (NO);
	if (ft_isalnum(c) || ft_isalpha(c) || c == '_')
		return (YES);
	else
		return (NO);
}

