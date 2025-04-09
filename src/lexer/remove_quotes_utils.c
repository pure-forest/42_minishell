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

char *check_quote_expansion(t_struct_ptrs *data, t_token **node, int *i, int *j)
{
	int	variable_length;
	char	*ret;

	variable_length = 0;
	while ((*node)->value[*i] && !ft_strchr("\'\"", (*node)->value[*i]))
	{
		(*i)++;
		variable_length++;
	}
	ret = ft_strndup(&((*node)->value)[*i - variable_length], variable_length);
	ret = expand_variable(data, ret);
	(*j) += ft_strlen(ret);
	(*node)->should_expand = NO;
	return (ret);
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
