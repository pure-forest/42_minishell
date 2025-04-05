#include "../../inc/lexer.h"

int	calculate_valid_word(char *str);

int	tokenize_text(char *str, int *i, t_token **token_list)
{
	char	*token_value;
	int		length;
	t_token	*node;

	token_value = NULL;
	node = NULL;
	length = calculate_valid_word(&str[*i]);
	if (length < 0)
		return (FAIL);
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

int	handle_quote(char *str, int *i, int *in_quote)
{
	int		index;
	char	quote_mark;

	index = 0;
	if (!str || !*str)
		return (*in_quote = 0, FAIL);
	if (!ft_strchr("\'\"", str[index]))
		return (*in_quote = 0, FAIL);
	quote_mark = str[index];
	index++;
	while (str[index])
	{
		if (str[index] == quote_mark)
		{
			(*i)++;
			*in_quote = 0;
			break ;
		}
		(*i)++;
		index++;
	}
	if (str[index] != quote_mark)
		return (FAIL);
	return (SUCCESS);
}

int	calculate_valid_word(char *str)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (str[i] && (!ft_strchr(FT_DELIMINATER, str[i]) || in_quote))
	{
		if (ft_strchr(FT_SPACE, str[i]) && in_quote == 0)
			break ;
		else if (ft_strchr("\"\'", str[i]))
		{
			in_quote = 1;
			if (handle_quote(&str[i], &i, &in_quote) == FAIL)
				return (-1);
		}
		i++;
	}
	return (i);
}
