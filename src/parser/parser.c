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

char	*here_doc_put_input(char *deliminator)
{
	// char	*ret;
	int		fd;
	char	*temp;

	// ret = ft_calloc(1, sizeof(char));
	fd = open("temp_file", O_RDWR | O_CREAT);
	while (1)
	{
		write(1, "> ", 2);
		temp = get_next_line(0);
		if (!ft_strncmp(temp, deliminator, ft_strlen(deliminator)))
		{
			free(temp);
			return (NULL);
		}
		else
		{
			write(fd, temp, ft_strlen(temp));
			free(temp);
		}
	}
	close(fd);
	return (NULL);
}

int	parse_heredoc(t_token *token_list, t_input **input)
{
	t_input *node;
	char	*string;

	(void)input;
	node = NULL;
	while (token_list)
	{
		if (token_list->type == HEREDOC)
		{
			string = here_doc_put_input(((t_token *)(token_list
			->base.next))->value);
			printf("string = %s\n", string);
		}
		token_list = (t_token *)(token_list->base.next);
	}
	return (SUCCESS);
}

t_input	*parser(t_token *token_list)
{
	t_input	*ret_input;

	ret_input = NULL;
	if (parse_cmd_args(token_list, &ret_input) == FAIL)
		return (NULL);
	if (parse_heredoc(token_list, &ret_input) == FAIL)
		return (NULL);
	// if (parse_redirection(token_list, &ret_input) == FAIL)
	return (ret_input);
}
