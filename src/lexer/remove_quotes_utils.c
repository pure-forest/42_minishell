#include "../../inc/lexer.h"

char	*check_quote_expansion(t_struct_ptrs *data, t_token **node, int *i,
		int *j)
{
	int		variable_length;
	char	*valid_variable;
	char	*ret;

	variable_length = 0;
	valid_variable = NULL;
	while ((!ft_strchr("\'\"", (*node)->value[*i])) && (*node)->value[*i])
	{
		(*i)++;
		variable_length++;
	}
	valid_variable = ft_strndup(&((*node)->value)[*i - variable_length], variable_length);
	if (!valid_variable)
		return (NULL);
	ret = expand_variable(data, valid_variable);
	if (!ret || !*ret)
	{
		free(ret);
		ret = NULL;
		(*j)++;
	}
	else
		(*j) += ft_strlen(ret);
	(*node)->should_expand = NO;
	free(valid_variable);
	valid_variable = NULL;
	return (ret);
}




