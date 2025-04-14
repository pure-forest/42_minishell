#include "../../inc/parsing.h"

static int	get_node_num(t_token *token_list);
static int	assign_value_cmd_arrs(t_input **input, t_token **token_list);
static int	parse_cmd_args(t_token **token_list, t_input **input);

t_input	*parser(t_struct_ptrs *data)
{
	t_input	*ret_input;

	ret_input = NULL;
	if (parse_heredoc(data) == FAIL)
		return (NULL);
	if (expand_word_token(data) == FAIL)
		return (NULL);
	if (parse_cmd_args(&data->token, &ret_input) == FAIL)
		return (NULL);
	if (parse_redirection(&data->token, &ret_input) == FAIL)
		return (NULL);
	print_input(ret_input);
	return (ret_input);
}

static int	get_node_num(t_token *token_list)
{
	int		node_num;

	node_num = 1;
	while (token_list)
	{
		if (token_list->type == PIPE)
			node_num++;
		token_list = (t_token *)(token_list->base.next);
	}
	return (node_num);
}

static int	assign_value_cmd_arrs(t_input **input, t_token **token_list)
{
	char	**cmd_arr;
	t_input	*new_node;
	int		size;
	int		i;

	i = 0;
	size = cmd_arr_num(*token_list);
	cmd_arr = ft_calloc(size + 1, sizeof(char *));
	while ((*token_list) && (*token_list)->type != PIPE)
	{
		if ((*token_list)->type == WORD)
		{
			cmd_arr[i] = ft_strdup((*token_list)->value);
			if (!cmd_arr[i])
				return (ft_free_double_ptr(cmd_arr), FAIL);
			i++;
		}
		(*token_list) = (t_token *)((*token_list)->base.next);
	}
	if (!cmd_arr)
		return (FAIL);
	cmd_arr[i] = NULL;
	new_node = cmd_table_init(cmd_arr);
	append_node((t_list_base **)input, (t_list_base *)new_node);
	get_next_cmd_node(token_list);
	return (SUCCESS);
}

static int	parse_cmd_args(t_token **token_list, t_input **input)
{
	int	node_num;
	t_token	*temp;

	temp = *token_list;
	node_num = get_node_num(temp);
	while (node_num >= 1)
	{
		if (assign_value_cmd_arrs(input, &temp) == FAIL)
			return (FAIL);
		node_num--;
	}
	return (SUCCESS);
}
