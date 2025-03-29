#include "../../inc/parsing.h"

t_input	*cmd_table_init(char **cmd_arr)
{
	t_input	*temp;

	temp = ft_calloc(3, sizeof(t_input));
	if (!temp)
		return (NULL);
	temp->cmd_arr = cmd_arr;
	temp->cmd = ft_strdup(cmd_arr[0]);
	return (temp);
}

int	cmd_arr_num(t_token *token_list)
{
	int	num = 0;

	while (token_list && token_list->type == WORD)
	{
		num++;
		token_list = (t_token *)(token_list->base.next);
	}
	return (num);
}

void	mock_execution(t_token *token_list)
{
	int	fd;

	while (token_list)
	{
		if (token_list->type == INFILE)
		{
			fd = open(token_list->value, O_RDONLY);
			printf("fd = %d\n", fd);
		}
		token_list = (t_token *)(token_list->base.next);
	}
}

t_input	*parser(t_token *token_list)
{
	char	**cmd_arr;
	int		size;
	t_input *temp;
	int		i;

	mock_execution(token_list);
	i = 0;
	temp = NULL;
	size = cmd_arr_num(token_list);
	cmd_arr = ft_calloc(size + 1, sizeof(char *));
	if (!cmd_arr)
		return (NULL);
	while (token_list && token_list->type == WORD)
	{
		cmd_arr[i] = ft_strdup(token_list->value);
		if (!cmd_arr[i])
			ft_free_double_ptr(cmd_arr);
		i++;
		token_list = (t_token *)(token_list->base.next);
	}
	cmd_arr[i++] = NULL;
	temp = cmd_table_init(cmd_arr);
	return (temp);
}

