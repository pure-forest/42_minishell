#include "../../inc/parsing.h"

int	check_redir_file(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == REDIR)
		{
			if (token_list->prev == NULL)
			{
				ft_putstr_fd("Catshell: syntax error near unexpected token `newline'\n", 2);
				return (ERROR);
			}
			if (token_list->prev->type == PIPE)
			{
				ft_putstr_fd("Catshell: syntax error near unexpected token `|'\n", 2);
				return (ERROR);
			}
			if (token_list->value[0] == '<')
				token_list->prev->type = INFILE;
			else if (token_list->value[0] == '>')
				token_list->prev->type = OUTFILE;
		}
		token_list = token_list->next;
	}
	return (0);
}

int	check_pipe(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == PIPE)
		{
			if (token_list->prev == NULL)
			{
				ft_putstr_fd("Catshell: syntax error near unexpected token `newline'\n", 2);
				return (ERROR);
			}
		}
		token_list = token_list->next;
	}
	return (0);
}
