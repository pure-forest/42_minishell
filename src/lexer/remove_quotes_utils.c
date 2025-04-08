#include "../../inc/lexer.h"

t_token	*get_quote_token(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == WORD
			&& (ft_strchr(token_list->value, '\'')
					|| ft_strchr(token_list->value, '\"')))
			return (token_list);
		token_list = ((t_token *)(token_list->base.next));
	}
	return (NULL);
}

int	get_character_number(char *src, char not_to_count)
{
	int i;
	int char_num;

	i = ft_strchr(src, not_to_count) - src + 1;
	char_num = 0;
	if (!src || !*src)
		return (0);
	while (src[i] != not_to_count)
	{
		char_num++;
		i++;
	}
	return (char_num);
}

char	get_quote_mark(char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (ft_strchr("\'\"", src[i]))
		{
			return (src[i]);
		}
		i++;
	}
	return (0);
}
