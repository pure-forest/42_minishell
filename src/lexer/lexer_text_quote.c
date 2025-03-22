#include "../../inc/lexer.h"

int		calculate_quote_length(char *str);
int		calculate_valid_word(char *str);

int		tokenize_text(char *str, int *i, t_token **token_list)
{
	char	*token_value;
	int		length;

	token_value = NULL;
	length = calculate_valid_word(&str[*i]);
	if (length > 0)
	{
		token_value = ft_substr(str, *i, length);
		if (!token_value)
			return (ERROR);
		push_to_list(WORD, token_value, token_list);
		*i += length;
	}
	return (0);
}

int		tokenize_quote(char *str, int *i, t_token **token_list)
{
	char	*token_value;
	int		length = 0;

	token_value = NULL;
	length = calculate_quote_length(&str[*i]);
	if (length == ERROR)
		return (ERROR);
	if (length > 0)
	{
		token_value = ft_substr(str, *i, length);
		if (!token_value)
			return (ERROR);
		push_to_list(WORD, token_value, token_list);
		*i += length;
	}
	return (0);
}

int		calculate_valid_word(char *str)
{
	int		i = 0;

	while (str[i])
	{
		if (ft_strchr(FT_SPACE, str[i]))
			break;
		else if (ft_strchr(FT_DELIMINATER, str[i]))
			break;
		else if (ft_strchr("\'\"", str[i]))
			break;
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
		printf("%p\n",str);
		if (str[i] == '\'' || str[i] == '\"')
			break;
		i++;
	}
	if (str[i] != '\'' && str[i] != '\"')
		return (ERROR);
	return (i + 1);
}
