#include "../../inc/expansion.h"

char	*expand_variable(t_struct_ptrs *data, char *src)
{
	char	*new_str;
	char	*expanded;
	int		i;

	if (!src || !*src)
		return (NULL);
	variable_init(&i, &new_str, &expanded);
	while (src[i])
	{
		if (expanded == NULL)
		{
			expanded = append_or_expand(src, &i, &new_str, data);
			if (!expanded)
				if (!new_str)
					return (free(new_str), free(src), NULL);
			if (src[i] == 0 && expanded)
				return (free(src), ft_strjoin_and_free(new_str, expanded));
		}
		else
		{
			new_str = ft_strjoin_and_free(new_str, expanded);
			expanded = NULL;
		}
	}
	return (free(src), new_str);
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
			else if (!ft_strcmp(node->expanded_value, ""))
			{
				free(node->expanded_value);
				node->expanded_value = NULL;
			}
			node->value = (node)->expanded_value;
		}
		node = (t_token *)(node->base.next);
	}
	return (SUCCESS);
}
