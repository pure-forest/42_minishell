#include "../../inc/lexer.h"

int	tokenize_pipe(char *str, int *i, t_token **token_list)
{
	char	*token_value;
	t_token	*node;

	node = NULL;
	if (str[*i] == '|')
	{
		token_value = ft_substr(str, *i, 1);
		if (!token_value)
			return (FAIL);
		node = token_init(PIPE, token_value);
		if (!node)
			return (FAIL);
		if (!(*token_list))
			(*token_list) = node;
		else if (append_node((t_list_base **)token_list,
			(t_list_base *)node) == FAIL)
			return (FAIL);
		(*i)++;
	}
	return (0);
}

int	tokenize_redir(char *str, int *i, t_token **token_list)
{
	char	*token_value;
	int		length;
	t_token	*node;

	length = 1;
	node = NULL;
	if (str[*i] == '<' || str[*i] == '>')
	{
		if (str[*i] == str[*i + 1])
			length++;
		token_value = ft_substr(str, *i, length);
		if (!token_value)
			return (FAIL);
		node = token_init(REDIR, token_value);
		if (!(*token_list))
			(*token_list) = node;
		else if (append_node((t_list_base **)token_list,
			(t_list_base *)node) == FAIL)
			return (FAIL);
		*i += length;
	}
	return (0);
}

