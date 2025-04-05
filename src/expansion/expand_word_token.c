#include "../../inc/expansion.h"

int	expand_word_token(t_struct_ptrs *data)
{
	t_token *node;
	char	*new_value;

	node = data->token;
	new_value = NULL;
	// print_token_list(node);
	while (node)
	{
		if (ft_strchr(node->value, '$'))
		{
			new_value = expand_variable(data, node->value);
			if (!new_value)
				return (FAIL);
			node->value = new_value;
		}
		node = (t_token *)(node->base.next);
	}
	return (SUCCESS);
}