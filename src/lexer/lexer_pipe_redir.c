#include "../../inc/lexer.h"

int	tokenize_pipe(char *str, int *i, t_token **token_list)
{
	char	*token_value;
	t_token	*node;

	node = NULL;
	if (str[*i] == '|')
	{
		token_value = ft_substr(str, *i, 1);
		printf("token_value = %s\n", token_value);
		if (!token_value)
			return (ERROR);
		node = node_init(PIPE, token_value);
		if (!node)
			return (ERROR);
		if (!(*token_list))
			(*token_list) = node;
		else if (append_node(node, *token_list) == ERROR)
			return (ERROR);
		(*i)++;
	}
	return (0);
}

int	tokenize_redir(char *str, int *i, t_token **token_list)
{
	char	*token_value;
	int		length;
	t_token	*node;

	length = 1;
	node = NULL;
	if (str[*i] == '<' || str[*i] == '>')
	{
		if (str[*i] == str[*i + 1])
			length++;
		token_value = ft_substr(str, *i, length);
		if (!token_value)
			return (ERROR);
		node = node_init(REDIR, token_value);
		if (!(*token_list))
			(*token_list) = node;
		else if (append_node(node, *token_list) == ERROR)
			return (ERROR);
		*i += length;
	}
	return (0);
}

t_token	*find_heredoc(t_token *token_list)
{
	t_token *heredoc_node;

	heredoc_node = NULL;
	while (token_list)
	{
		if (token_list->type == HEREDOC)
			return (token_list);
		token_list = token_list->next;
	}
	return (heredoc_node);
}

// int	create_heredoc_string_node(char *str, t_token *heredoc_node)
// {
// 	t_token *node;
// 	t_token *prev;
// 	t_token *next;

// 	node = node_init(WORD, str);
// 	if (!node)
// 		return (ERROR);
// 	next = heredoc_node->next->next;
// 	prev = heredoc_node->prev;
// 	prev->next = node;
// 	next->prev = node;
// 	free(heredoc_node->next);
// 	free(heredoc_node->value);
// 	return (0);
// }

// int	tokenize_heredoc(t_token **token_list)
// {
// 	t_token *heredoc_node;
// 	char	*readline_str;
// 	char	*deliminator;
// 	char	*full_string;

// 	heredoc_node = find_heredoc(*token_list);
// 	full_string = ft_calloc(1, sizeof(char));
// 	if (!heredoc_node)
// 		return (0);
// 	deliminator = heredoc_node->next->value;
// 	while (1)
// 	{
// 		readline_str = readline("> ");
// 		if (!ft_strncmp(readline_str, deliminator, ft_strlen(deliminator)))
// 			break;
// 		printf("readline_str = %s\n", readline_str);
// 		readline_str = ft_strjoin(readline_str, "\n");
// 		full_string = ft_strjoin(full_string, readline_str);
// 		printf("full string = %s\n", full_string);
// 	}
// 	create_heredoc_string_node(full_string, heredoc_node);
// 	return (0);
// }
