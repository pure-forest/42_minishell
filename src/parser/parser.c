#include "../../inc/parsing.h"

int	parse_cmd_args(t_token *token_list, t_input **input)
{
	char	**cmd_arr;
	int		size;
	t_input	*temp;
	int		i;

	i = 0;
	temp = NULL;
	size = cmd_arr_num(token_list);
	cmd_arr = ft_calloc(size + 1, sizeof(char *));
	if (!cmd_arr)
		return (FAIL);
	while (token_list && token_list->type == WORD)
	{
		cmd_arr[i] = ft_strdup(token_list->value);
		if (!cmd_arr[i])
			return (ft_free_double_ptr(cmd_arr), FAIL);
		i++;
		token_list = (t_token *)(token_list->base.next);
	}
	cmd_arr[i++] = NULL;
	temp = cmd_table_init(cmd_arr);
	if (append_node((t_list_base **)input, (t_list_base *)temp) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

t_input	*parser(t_struct_ptrs *data)
{
	t_input	*ret_input;

	ret_input = NULL;
	if (expand_word_token(data) == FAIL)
		return (free_lexer(&data->token), NULL);
	if (parse_cmd_args(data->token, &ret_input) == FAIL)
		return (NULL);
	if (parse_heredoc(data) == FAIL)
		return (NULL);
	// if (parse_redirection(token_list, &ret_input) == FAIL)
	return (ret_input);
}
