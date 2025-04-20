#include "../../inc/expansion.h"

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
			else if (!ft_strncmp(node->expanded_value, "", 1))
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
