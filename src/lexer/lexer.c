#include "../../inc/lexer.h"

t_token *create_token_list(char *str)
{
	t_token *token_list;
	int		i;

	token_list = NULL;
	i = 0;
	while (str && str[i])
	{
		if (tokenize_pipe(str, &i, &token_list) == ERROR)
			break ;
		if (tokenize_redir(str, &i, &token_list) == ERROR)
		 	break;
		if (tokenize_text(str, &i, &token_list) == ERROR)
			break;
		if (tokenize_quote(str, &i, &token_list) == ERROR)
			break;
		while (str[i] && ft_strchr(FT_SPACE, str[i]))
			i++;
	}
	if (str[i] != '\0')
		return (NULL);
	return (token_list);
}

t_token	*lexer(char *str)
{
	t_token *token_list;

	token_list = create_token_list(str);
	if (!token_list)
	{
		ft_putstr_fd("Error\n", 2);
		return (NULL);
	}
	if (check_pipe(token_list) == ERROR)
		return (free_lexer(&token_list), NULL);
	if (check_redir_file(token_list) == ERROR)
		return (free_lexer(&token_list), NULL);
	if (check_heredoc(token_list) == ERROR)
		return (free_lexer(&token_list), NULL);
	return (token_list);
}
