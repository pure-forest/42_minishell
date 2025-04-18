#include "../../inc/lexer.h"

static int	modify_quote_node(t_token **node, t_struct_ptrs *data);
static char	*trim_quotes_and_expand(t_struct_ptrs *data, t_token **node);
static void	modify_quote_mark(int *i, t_token **node);
static int	strcpy_or_expand(t_struct_ptrs *data, t_token **node,
				int *i, int *j);

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
			if (modify_quote_node(&node, data) == FAIL)
				return (FAIL);
			node = (t_token *)(node->base.next);
		}
		node = get_quote_token(node);
	}
	return (SUCCESS);
}

static int	modify_quote_node(t_token **node, t_struct_ptrs *data)
{
	(*node)->expanded_value = ft_calloc(ft_strlen((*node)->value),
			sizeof(char));
	if (!(*node)->expanded_value)
		return (FAIL);
	(*node)->expanded_value = trim_quotes_and_expand(data, node);
	if (!(*node)->expanded_value)
		return (free((*node)->expanded_value), FAIL);
	free((*node)->value);
	(*node)->value = (*node)->expanded_value;
	(*node)->expand_heredoc = NO;
	(*node)->should_expand = NO;
	return (SUCCESS);
}

static char	*trim_quotes_and_expand(t_struct_ptrs *data, t_token **node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*node)->value[i])
	{
		if (((*node)->quote_count == 0 && ((*node)->value[i] == '\''
					|| (*node)->value[i] == '\"'))
			|| (*node)->value[i] == (*node)->quote_mark)
			modify_quote_mark(&i, node);
		else
		{
			if (strcpy_or_expand(data, node, &i, &j) == FAIL)
				return (free((*node)->expanded_value), NULL);
		}
	}
	return ((*node)->expanded_value);
}

static void	modify_quote_mark(int *i, t_token **node)
{
	(*node)->quote_count++;
	if ((*node)->quote_mark == 0)
	{
		(*node)->quote_mark = get_quote_mark(&((*node)->value[*i]));
		(*i)++;
		return ;
	}
	if ((*node)->value[*i] == (*node)->quote_mark)
	{
		if ((*node)->quote_count == 2 && (*node)->value[*i])
		{
			(*i)++;
			(*node)->quote_mark = get_quote_mark(&((*node)->value[*i]));
			(*node)->quote_count = 0;
			return ;
		}
		else if ((*node)->quote_count == 1)
		{
			(*i)++;
			return ;
		}
	}
}

static int	strcpy_or_expand(t_struct_ptrs *data, t_token **node, int *i,
		int *j)
{
	char	*temp;

	temp = NULL;
	if (((t_token *)((*node)->base.prev)
		&& ((t_token *)((*node)->base.prev))->type == HEREDOC)
		|| should_expand((*node)->value[*i], (*node)->quote_mark) == NO)
	{
		(*node)->expanded_value
			= append_character_in_string(((*node)->expanded_value),
				(*node)->value[*i]);
		if (!((*node)->expanded_value))
			return (FAIL);
		(*j)++;
		(*i)++;
	}
	else
	{
		((*node)->expanded_value)[*j] = 0;
		temp = check_quote_expansion(data, node, i, j);
		(*node)->expanded_value = ft_strjoin_and_free(((*node)->expanded_value),
				temp);
		if (!((*node)->expanded_value))
			return (free(temp), FAIL);
	}
	return (SUCCESS);
}
