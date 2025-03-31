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
			return (FAIL);
		node = token_init(WORD, token_value);
		if (!node)
			return (FAIL);
		if (!(*token_list))
			(*token_list) = node;
		else if (append_node((t_list_base **)token_list,
				(t_list_base *)node) == FAIL)
			return (FAIL);
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
	if (length == FAIL)
		return (FAIL);
	if (length > 0)
	{
		token_value = ft_substr(str, *i + 1, length - 2);
		if (!token_value)
			return (FAIL);
		node = token_init(WORD, token_value);
		if (!node)
			return (FAIL);
		if (append_node((t_list_base **)token_list,
				(t_list_base *)node) == FAIL)
			return (FAIL);
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
	int		i;
	char	quote_mark;

	// printf("str = %s\n", str);
	if (!str || !*str)
		return (0);
	if (!ft_strchr("\'\"", str[0]))
		return (0);
	quote_mark = str[0];
	i = 1;
	while (str[i])
	{
		if (str[i] == quote_mark)
			break;
		i++;
	}
	if (str[i] != quote_mark)
		return (FAIL);
	return (i + 1);
}
