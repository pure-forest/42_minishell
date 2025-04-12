#include "../../inc/expansion.h"

static char	*chop_valid_variable(char *src, int *i);
static char	*append_or_expand(char *src, int *i, char **new_str,
				t_struct_ptrs *data);
static char	*expand_valid_variable(char *valid_variable, t_struct_ptrs *data);

int	expand_word_token(t_struct_ptrs *data)
{
	t_token	*node;

	node = data->token;
	while (node)
	{
		if (node->should_expand == YES && ft_strchr(node->value, '$'))
		{
			(node)->expanded_value = expand_variable(data, node->value);
			if (!(node)->expanded_value)
				return (FAIL);
			free(node->value);
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
			expanded_value = append_or_expand(src, &i, &new_str, data);
			if (src[i] == 0)
				return (ft_strjoin_and_free(new_str, expanded_value));
		}
		else
		{
			new_str = ft_strjoin_and_free(new_str, expanded_value);
			expanded_value = NULL;
		}
	}
	return (new_str);
}

static char	*append_or_expand(char *src, int *i, char **new_str,
		t_struct_ptrs *data)
{
	char	*expand_value;
	char	*valid_variable;

	expand_value = NULL;
	valid_variable = NULL;
	if (should_just_append(src[*i], &src[*i]) == YES)
	{
		*new_str = append_character_in_string(*new_str, src[(*i)++]);
		return (NULL);
	}
	else
	{
		valid_variable = chop_valid_variable(src, i);
		expand_value = expand_valid_variable(valid_variable, data);
	}
	return (expand_value);
}

static char	*chop_valid_variable(char *src, int *i)
{
	char	*valid_variable;
	int		j;

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
	return (valid_variable);
}

static char	*expand_valid_variable(char *valid_variable, t_struct_ptrs *data)
{
	t_env_nodes	*temp;
	char		*ret;

	temp = data->env;
	ret = NULL;
	if (!ft_strncmp(valid_variable, "$=", 2))
		return (free(valid_variable), ft_itoa(getpid()));
	else if (!get_var_value(temp, valid_variable))
		ret = NULL;
	else
		ret = ft_strdup(get_var_value(temp, valid_variable));
	free(valid_variable);
	if (!ret)
		return (ft_strdup(""));
	else
		return (ret);
}
