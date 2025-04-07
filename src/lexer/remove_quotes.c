#include "../../inc/lexer.h"

static char	*trim_quotes_magic(t_token **node, char *new_str)
{
	char	quote_mark;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote_mark = get_quote_mark((*node)->value);
	while ((*node)->value[i])
	{
		if ((*node)->value[i] != quote_mark)
			new_str[j++] = (*node)->value[i++];
		else
		{
			i++;
			(*node)->quote_count++;
			if ((*node)->quote_count == 2 && (*node)->value[i])
			{
				quote_mark = get_quote_mark(&((*node)->value[i]));
				(*node)->quote_count = 0;
			}
		}
	}
	new_str[j] = '\0';
	return (new_str);
}

static void	check_for_expand(char *new_str, t_token **node)
{

	if (ft_strchr(new_str, '\"'))
		(*node)->should_expand = NO;
}

static int	remove_quotes_nodes(t_token **node)
{
	char	*new_str;

	new_str = ft_calloc(ft_strlen((*node)->value), sizeof(char));
	if (!new_str)
		return (FAIL);
	new_str = trim_quotes_magic(node, new_str);
	check_for_expand(new_str, node);
	if (!new_str)
		return (FAIL);
	free((*node)->value);
	(*node)->value = new_str;
	return (SUCCESS);
}

int	remove_quotes(t_token *token_list, t_struct_ptrs *data)
{
	t_token	*node;

	node = get_quote_token(token_list);
	(void)data;
	if (!node)
		return (SUCCESS);
	while (node)
	{
		if ((ft_strchr(node->value, '\'') || ft_strchr(node->value, '\"')))
		{
			remove_quotes_nodes(&node);
			node = (t_token *)(node->base.next);
		}
		node = get_quote_token(node);
	}
	return (SUCCESS);
}
