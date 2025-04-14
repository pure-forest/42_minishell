#include "../../inc/lexer.h"

static char	*trim_quotes_and_expand(t_struct_ptrs *data, t_token **node,
				char *new_str);
static int	modify_quote_node(t_token **node, t_struct_ptrs *data);
static void	modify_quote_mark(int *i, t_token **node);
static int	strcpy_or_expand(t_struct_ptrs *data, t_token **node,
				char **new_str, int *i, int *j);

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
	char	*new_str;

	new_str = ft_calloc(ft_strlen((*node)->value), sizeof(char));
	if (!new_str)
		return (FAIL);
	new_str = trim_quotes_and_expand(data, node, new_str);
	if (!new_str)
		return (FAIL);
	free((*node)->value);
	(*node)->value = new_str;
	(*node)->expand_heredoc = NO;
	(*node)->should_expand = NO;
	return (SUCCESS);
}

static char	*trim_quotes_and_expand(t_struct_ptrs *data, t_token **node,
		char *new_str)
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
			if (strcpy_or_expand(data, node, &new_str, &i, &j) == FAIL)
				return (NULL);
		}
	}
	return (new_str);
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

static int	strcpy_or_expand(t_struct_ptrs *data, t_token **node,
		char **new_str, int *i, int *j)
{
	char	*temp;

	temp = (*node)->expanded_value;
	if (((t_token *)((*node)->base.prev))->type == HEREDOC
		|| should_expand((*node)->value[*i], (*node)->quote_mark) == NO)
	{
		*new_str = append_character_in_string((*new_str), (*node)->value[*i]);
		if (!(*new_str))
			return (FAIL);
		(*j)++;
		(*i)++;
	}
	else
	{
		(*new_str)[*j] = 0;
		temp = check_quote_expansion(data, node, i, j);
		*new_str = ft_strjoin_and_free((*new_str), temp);
		if (!(*new_str))
			return (FAIL);
	}
	return (SUCCESS);
}
