#include "../../inc/lexer.h"

static char	*trim_quotes_and_expand(t_struct_ptrs *data, t_token **node, char *new_str);
static int	modify_quote_node(t_token **node, t_struct_ptrs *data);
static bool	should_expand(char c, char quote_mark);
static void	modify_quote_mark(int *i, t_token **node, char *quote_mark);

int	remove_quotes(t_struct_ptrs *data)
{
	t_token	*node;

	node = get_quote_token(data->token);
	if (!node)
		return (SUCCESS);
	while (node)
	{
		if ((ft_strchr(node->value, '\'') || ft_strchr(node->value, '\"')))
		{
			modify_quote_node(&node, data);
			node = (t_token *)(node->base.next);
		}
		node = get_quote_token(node);
	}
	return (SUCCESS);
}

static int	modify_quote_node(t_token **node, t_struct_ptrs *data)
{
	char	*new_str;

	new_str = ft_calloc(ft_strlen((*node)->value), sizeof(char));
	if (!new_str)
		return (FAIL);
	new_str = trim_quotes_and_expand(data, node, new_str);
	if (!new_str)
		return (FAIL);
	free((*node)->value);
	(*node)->value = new_str;
	return (SUCCESS);
}

static char	*trim_quotes_and_expand(t_struct_ptrs *data, t_token **node, char *new_str)
{
	char	quote_mark;
	char	*expand_value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote_mark = get_quote_mark(&((*node)->value[i]));
	while ((*node)->value[i])
	{
		expand_value = NULL;
		if ((*node)->value[i] != quote_mark)
		{
			if (should_expand((*node)->value[i], quote_mark) == NO)
				new_str[j++] = (*node)->value[i++];
			else
			{
				new_str[j] = 0;
				expand_value = check_quote_expansion(data, node, &i, &j);
				new_str = ft_strjoin_and_free(new_str, expand_value);
				if (!new_str)
					return (NULL);
			}
		}
		else
			modify_quote_mark(&i, node, &quote_mark);
	}
	new_str[j] = 0;
	return (new_str);
}

static void	modify_quote_mark(int *i, t_token **node, char *quote_mark)
{
	(*i)++;
	(*node)->quote_count++;
	if ((*node)->quote_count == 2 && (*node)->value[*i])
	{
		*quote_mark = get_quote_mark(&((*node)->value[*i]));
		(*node)->quote_count = 0;
	}
	else if ((*node)->quote_count != 2)
		return ;
	return ;
}

static bool	should_expand(char c, char quote_mark)
{
	if (c != quote_mark && quote_mark == '\'')
		return (NO);
	else
		return (YES);
}
