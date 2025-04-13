#include "../../inc/lexer.h"

static t_token	*lexer(char *str, t_struct_ptrs *data);
static t_token	*create_token_list(char *str);

int	start_tokenization(char *read_line, t_struct_ptrs *data)
{
	signal_init();
	data->token = lexer(read_line, data);
	free(read_line);
	if (!data->token)
	{
		printf("lexer failure\n");
		return (FAIL);
	}
	if (remove_quotes(data) == FAIL)
	{
		free(data->token);
		printf("remove quotes failed\n");
		return (FAIL);
	}
	// print_token_list(data->token);
	data->input = parser(data);
	if (!data->input)
	{
		printf("parser failure\n");
		return (FAIL);
	}
	return (SUCCESS);
}

static t_token	*create_token_list(char *str)
{
	t_token	*token_list;
	int		i;

	i = 0;
	token_list = NULL;
	while (str && str[i])
	{
		// if (ft_strchr(";&()\\", str[i]))
		// 	break ;
		if (tokenize_pipe(str, &i, &token_list) == FAIL)
			break ;
		if (tokenize_redir(str, &i, &token_list) == FAIL)
			break ;
		if (tokenize_text(str, &i, &token_list) == FAIL)
			break ;
		while (str && str[i] && ft_strchr(FT_SPACE, str[i]))
			i++;
	}
	if (str[i] != '\0')
		return (NULL);
	return (token_list);
}

static t_token	*lexer(char *str, t_struct_ptrs *data)
{
	t_token	*token_list;

	if (!str || !*str)
		return (NULL);
	token_list = create_token_list(str);
	if (!token_list)
		return (NULL);
	if (check_pipe(token_list, data) == FAIL)
		return (free_lexer(&token_list), NULL);
	if (check_redir_file(token_list) == FAIL)
		return (free_lexer(&token_list), NULL);
	if (check_heredoc(token_list) == FAIL)
		return (free_lexer(&token_list), NULL);
	return (token_list);
}
