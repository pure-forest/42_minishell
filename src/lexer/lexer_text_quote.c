#include "../../inc/lexer.h"

int	calculate_quote_length(char *str);
int	calculate_valid_word(char *str);

int	tokenize_text(char *str, int *i, t_token **token_list)
{
	char	*token_value;
	int		length;
	t_token	*node;

	token_value = NULL;
	node = NULL;
	length = calculate_valid_word(&str[*i]);
	if (length > 0)
	{
		token_value = ft_substr(str, *i, length);
		if (!token_value)
			return (ERROR);
		node = node_init(WORD, token_value);
		if (!node)
			return (ERROR);
		if (!(*token_list))
			(*token_list) = node;
		else if (append_node(node, *token_list) == ERROR)
			return (ERROR);
		*i += length;
	}
	return (0);
}

int	tokenize_quote(char *str, int *i, t_token **token_list)
{
	char	*token_value;
	int		length;
	t_token	*node;

	length = 0;
	token_value = NULL;
	node = NULL;
	length = calculate_quote_length(&str[*i]);
	if (length == ERROR)
		return (ERROR);
	if (length > 0)
	{
		token_value = ft_substr(str, *i, length);
		if (!token_value)
			return (ERROR);
		node = node_init(WORD, token_value);
		if (!node)
			return (ERROR);
		if (!(*token_list))
			(*token_list) = node;
		else if (append_node(node, *token_list) == ERROR)
			return (ERROR);
		*i += length;
	}
	return (0);
}

int	calculate_valid_word(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(FT_SPACE, str[i]))
			break ;
		else if (ft_strchr(FT_DELIMINATER, str[i]))
			break ;
		else if (ft_strchr("\'\"", str[i]))
			break ;
		i++;
	}
	return (i);
}

int	calculate_quote_length(char *str)
{
	int	i;

	if (!str || !*str || !ft_strchr("\'\"", str[0]))
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			break ;
		i++;
	}
	if (str[i] != '\'' && str[i] != '\"')
		return (ERROR);
	return (i + 1);
}
