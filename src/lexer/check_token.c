#include "../../inc/parsing.h"

int	check_redir_file(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == REDIR)
		{
			if (token_list->next == NULL || token_list->next->type == REDIR)
			{
				ft_putstr_fd("Catshell: syntax error near unexpected token `newline'\n", 2);
				return (ERROR);
			}
			if (!ft_strncmp(token_list->value, "<", 2))
			{
				token_list->type = INPUT;
				token_list->next->type = INFILE;
			}
			else if (!ft_strncmp(token_list->value, ">", 2))
			{
				token_list->type = OUTPUT;
				token_list->next->type = OUTFILE;
			}
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
			if (token_list->prev == NULL || token_list->next->type == PIPE)
			{
				ft_putstr_fd("Catshell: syntax error near unexpected token `|'\n", 2);
				return (ERROR);
			}
			if (token_list->prev->type == REDIR)
			{
				ft_putstr_fd("Catshell: syntax error near unexpected token `newline'\n", 2);
				return (ERROR);
			}
		}
		token_list = token_list->next;
	}
	return (0);
}

int	check_heredoc(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == REDIR)
		{
			if (!ft_strncmp(token_list->value, "<<", 3))
			{
				token_list->type = HEREDOC;
				if (token_list->next == NULL)
					return (ERROR);
			}
			else if (!ft_strncmp(token_list->value, ">>", 3))
			{
				token_list->type = OUTPUT;
				token_list->next->type = OUTFILE;
			}
		}
		token_list = token_list->next;
	}
	return (0);
}
