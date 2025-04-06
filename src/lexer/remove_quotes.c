#include "../../inc/lexer.h"

static int trim_single_quote(t_token **node, char *old_value, int *index)
{
	int chara_num;
	int i;
	int j;
	char *ret;

	chara_num = get_character_number(old_value, '\'');
	i = 0;
	j = 0;
	ret = ft_calloc(chara_num, sizeof(char));
	if (!ret)
		return (FAIL);
	while (old_value[i])
	{
		if (old_value[i] != '\'')
			ret[j++] = old_value[i++];
		else
			i++;
	}
	*index += j;
	ret[j] = '\0';
	free((*node)->value);
	(*node)->value = ret;
	(*node)->removed_quote = YES;
	return (SUCCESS);
}

static int trim_double_quote(t_token **node, char *old_value, int *index)
{
	int chara_num;
	int i;
	int j;
	char *ret;

	chara_num = get_character_number(old_value, '\"');
	i = 0;
	j = 0;
	ret = ft_calloc(chara_num, sizeof(char));
	if (!ret)
		return (FAIL);
	while (old_value[i])
	{
		if (old_value[i] != '\"')
			ret[j++] = old_value[i++];
		else
			i++;
	}
	ret[j] = '\0';
	*index += j;
	free((*node)->value);
	(*node)->value = ret;
	(*node)->removed_quote = YES;
	return (SUCCESS);
}

static int remove_quotes_nodes(t_token *node)
{
	bool in_single_quotes;
	bool in_double_quotes;
	int i = 0;

	in_single_quotes = NO;
	in_double_quotes = NO;
	while (node->value[i])
	{
		if (ft_strchr("\'", node->value[i]) && in_double_quotes == NO)
		{
			in_single_quotes = YES;
			if (trim_single_quote(&node, node->value, &i) == FAIL)
				return (FAIL);
			in_single_quotes = NO;
		}
		if (ft_strchr("\"", node->value[i]) && in_single_quotes == NO)
		{
			in_double_quotes = YES;
			if (trim_double_quote(&node, node->value, &i) == FAIL)
				return (FAIL);
			in_double_quotes = NO;
		}
		i++;
	}
	return (SUCCESS);
}

int remove_quotes(t_token *token_list)
{
	t_token *node;

	node = get_quote_token(token_list);
	while (node)
	{
		if (remove_quotes_nodes(node) == FAIL)
			return (FAIL);
		node = get_quote_token(node);
	}
	return (SUCCESS);
}
