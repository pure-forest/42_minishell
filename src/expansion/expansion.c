#include "../../inc/expansion.h"

char	*expand_variable(t_struct_ptrs *data, char *src)
{
	char	*new_str;
	char	*expanded_value;
	int		i;

	if (!src || !*src)
		return (NULL);
	variable_init(&i, &new_str, &expanded_value);
	while (src[i])
	{
		if (expanded_value == NULL)
		{
			expanded_value = append_or_expand(src, &i, &new_str, data);
			if (!expanded_value)
				if (!new_str)
					return (free(new_str), NULL);
			if (src[i] == 0 && expanded_value)
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

int	expand_word_token(t_struct_ptrs *data)
{
	t_token	*node;

	node = data->token;
	while (node)
	{
		if (node->should_expand == YES && ft_strchr(node->value, '$'))
		{
			(node)->expanded_value = expand_variable(data, node->value);
			if (!node->expanded_value)
				return (FAIL);
			else if (!ft_strncmp(node->expanded_value, "", 1))
			{
				free(node->expanded_value);
				node->expanded_value = NULL;
			}
			free(node->value);
			node->value = (node)->expanded_value;
		}
		node = (t_token *)(node->base.next);
	}
	return (SUCCESS);
}
