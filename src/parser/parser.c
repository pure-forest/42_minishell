#include "../../inc/parsing.h"

int	cmd_arr_num(t_token *token_list)
{
	int	num;

	num = 0;
	while (token_list && token_list->type == WORD)
	{
		num++;
		token_list = (t_token *)(token_list->base.next);
	}
	return (num);
}

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

void	here_doc_put_input(int	*pipe_fd, char *deliminator)
{
	char *ret;

	close(pipe_fd[0]);
	while (1)
	{
		ret = readline("> ");
		if (ret && !ft_strncmp(ret, deliminator, ft_strlen(deliminator)))
		{
			free(ret);
			return ;
		}
		else
		{
			ft_putstr_fd(ret, pipe_fd[1]);
			free(ret);
		}
	}
}

int	parse_heredoc(t_token *token_list, t_input **input)
{
	t_input *node;
	int		pipe_fd[2];
	pid_t	pid;

	(void)input;
	node = NULL;
	if (pipe(pipe_fd) == -1)
		exit(0);
	pid = fork();
	printf("pid = %d\n", pid);
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		while (token_list)
		{
			if (token_list->type == HEREDOC)
				here_doc_put_input(pipe_fd, ((t_token *)(token_list->base.next))->value);
			token_list = (t_token *)(token_list->base.next);
		}
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		wait(NULL);
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
	if (parse_redirection(token_list, &ret_input) == FAIL)
	return (ret_input);
}
