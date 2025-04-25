#include "../../inc/lexer.h"

bool	should_expand(char c, char quote_mark)
{
	if (quote_mark == '\'')
		return (NO);
	else if (quote_mark == '\"' && c == '\'')
		return (NO);
	else if (c != '$')
		return (NO);
	else
		return (YES);
}

bool	should_expand_node(t_token **node, int *i)
{
	if ((t_token *)((*node)->base.prev)
		&& ((t_token *)((*node)->base.prev))->type == HEREDOC)
		return (NO);
	if (should_expand((*node)->value[*i], (*node)->quote_mark) == NO)
		return (NO);
	return (YES);
}

int	get_character_number(char *src, char not_to_count)
{
	int	i;
	int	char_num;

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

char	get_quote_mark(char c)
{
	if (ft_strchr("\'\"", c))
	{
		return (c);
	}
	return (0);
}

t_token	*get_quote_token(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	while (temp)
	{
		if ((ft_strchr(temp->value, '\'') || ft_strchr(temp->value, '\"'))
			&& (temp->type == WORD || temp->type == INFILE
				|| temp->type == OUTFILE))
			return (temp);
		temp = ((t_token *)(temp->base.next));
	}
	return (NULL);
}
