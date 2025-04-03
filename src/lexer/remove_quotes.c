#include "../../inc/lexer.h"

char	*trim_single_quote(char  *old_value, int *index)
{
	int		chara_num;
	int		i;
	int		j;
	char	*ret;

	chara_num = 0;
	i = 0;
	j = 0;
	while (old_value[i])
	{
		if (old_value[i] != '\'')
			chara_num++;
		i++;
	}
	i = 0;
	ret = ft_calloc(chara_num, sizeof(char));
	while (old_value[i])
	{
		if (old_value[i] != '\'')
			ret[j++] = old_value[i++];
		else
			i++;
	}
	*index += j;
	ret[j] = '\0';
	return  (ret);
}

t_token *get_quote_token(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->removed_quote == NO && token_list->type == WORD
			&& (ft_strchr(token_list->value, '\'')
			|| ft_strchr(token_list->value, '\"')))
			return (token_list);
		token_list = ((t_token *)(token_list->base.next));
	}
	return (NULL);
}

char	*trim_double_quote(char *old_value, int *index)
{
	int		chara_num;
	int		i;
	int		j;
	char	*ret;

	chara_num = 0;
	i = 0;
	j = 0;
	while (old_value[i])
	{
		if (old_value[i] != '\"')
			chara_num++;
		i++;
	}
	i = 0;
	ret = ft_calloc(chara_num, sizeof(char));
	while (old_value[i])
	{
		if (old_value[i] != '\"')
			ret[j++] = old_value[i++];
		else
			i++;
	}
	ret[j] = '\0';
	*index += j;
	return  (ret);
}

int	remove_quotes(t_token *token_list, t_struct_ptrs *data)
{
	char	*new_value;
	bool	in_single_quotes;
	bool	in_double_quotes;
	t_token	*node;
	int		i = 0;

	in_single_quotes = NO;
	in_double_quotes = NO;
	new_value = NULL;
	node = get_quote_token(token_list);
	while (node)
	{
		while (node->value[i])
		{
			if (ft_strchr("\'", node->value[i]) && in_double_quotes == NO)
			{
				printf("are we here? trim single quote\n");
				in_single_quotes = YES;
				new_value = trim_single_quote(node->value, &i);
				free(node->value);
				node->value = NULL;
				node->value = new_value;
				node->removed_quote = YES;
			}
			else if (ft_strchr("\"", node->value[i]) && in_single_quotes == NO)
			{
				printf("trim double quote\n");
				in_double_quotes = YES;
				new_value = trim_double_quote(node->value, &i);
				printf("new_value = %s\n", new_value);
				data->should_expand = YES;
				free(node->value);
				node->value = new_value;
				node->removed_quote = YES;
			}
			i++;
			printf("node->value[%d] = %c\n", i, node->value[i]);
		}
		node = get_quote_token(token_list);
		printf("node  = %s\n", node->value);
	}
	return (0);
}
