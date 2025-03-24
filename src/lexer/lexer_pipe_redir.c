#include "../../inc/lexer.h"

int	tokenize_pipe(char *str, int *i, t_token **token_list)
{
	char	*token_value;
	t_token	*node;

	node = NULL;
	if (str[*i] == '|')
	{
		token_value = ft_substr(str, *i, 1);
		printf("token_value = %s\n", token_value);
		if (!token_value)
			return (ERROR);
		node = node_init(PIPE, token_value);
		if (!node)
			return (ERROR);
		if (!(*token_list))
			(*token_list) = node;
		else if (append_node(node, *token_list) == ERROR)
			return (ERROR);
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
			return (ERROR);
		node = node_init(REDIR, token_value);
		if (!(*token_list))
			(*token_list) = node;
		else if (append_node(node, *token_list) == ERROR)
			return (ERROR);
		*i += length;
	}
	return (0);
}
