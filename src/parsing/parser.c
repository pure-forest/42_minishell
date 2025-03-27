#include "../../inc/parsing.h"

t_cmd_table	*cmd_table_init(char **cmd_args)
{
	t_cmd_table	*temp;

	temp = ft_calloc(1, sizeof(t_cmd_table *));
	if (!temp)
		return (NULL);
	temp->cmd_args = cmd_args;
	return (temp);
}

int	cmd_args_num(t_token *token_list)
{
	int	num = 0;

	while (token_list && token_list->type == WORD)
	{
		num++;
		token_list = (t_token *)(token_list->base.next);
	}
	return (num);
}

t_cmd_table	*parser(t_token *token_list)
{
	char	**cmd_args;
	int		size;
	t_cmd_table *temp;
	int		i;

	i = 0;
	temp = NULL;
	size = cmd_args_num(token_list);
	cmd_args = ft_calloc(size + 1, sizeof(char *));
	if (!cmd_args)
		return (NULL);
	while ((t_token *)(token_list) && token_list->type == WORD)
	{
		cmd_args[i] = ft_strdup(token_list->value);
		i++;
		token_list = (t_token *)(token_list->base.next);
	}
	cmd_args[i++] = NULL;
	temp = cmd_table_init(cmd_args);
	return (temp);
}
