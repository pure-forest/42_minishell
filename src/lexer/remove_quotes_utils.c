#include "../../inc/lexer.h"

static char	*valid_variable_init(t_token **node, int *i);

char	*check_quote_expansion(t_struct_ptrs *data, t_token **node, int *i,
		int *j)
{
	char	*ret;
	char	*valid_variable;

	valid_variable = valid_variable_init(node, i);
	ret = expand_variable(data, valid_variable);
	if (!ret)
	{
		free_and_null(&ret);
		free_and_null(&valid_variable);
		(*j)++;
	}
	else if (!*ret)
	{
		free_and_null(&ret);
		(*j)++;
	}
	else
		(*j) += ft_strlen(ret);
	(*node)->should_expand = NO;
	return (ret);
}

static char	*valid_variable_init(t_token **node, int *i)
{
	int		length;
	char	*valid_variable;

	length = 0;
	valid_variable = NULL;
	while ((!ft_strchr("\'\"", (*node)->value[*i])) && (*node)->value[*i])
	{
		(*i)++;
		length++;
	}
	valid_variable = ft_strndup(&((*node)->value)[*i - length], length);
	if (!valid_variable)
		return (NULL);
	return (valid_variable);
}
