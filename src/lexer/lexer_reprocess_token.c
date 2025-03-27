#include "../../inc/lexer.h"

int	check_redir_file(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == REDIR)
		{
			if (token_list->base.next == NULL || ((t_token *)(token_list
			->base.next))->type == REDIR)
			{
				ft_putstr_fd("Catshell: syntax error near unexpected token `newline'\n", 2);
				return (ERROR);
			}
			if (!ft_strncmp(token_list->value, "<", 2))
			{
				token_list->type = INPUT;
				((t_token *)(token_list->base.next))->type = INFILE;
			}
			else if (!ft_strncmp(token_list->value, ">", 2))
			{
				token_list->type = OUTPUT;
				((t_token *)(token_list->base.next))->type = OUTFILE;
			}
		}
		token_list = (t_token *)(token_list->base.next);
	}
	return (0);
}

int	check_pipe(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == PIPE)
		{
			if ((t_token *)(token_list->base.prev) == NULL ||
				((t_token *)(token_list->base.next))->type == PIPE)
			{
				ft_putstr_fd("Catshell: syntax error near unexpected token `|'\n", 2);
				return (ERROR);
			}
			if (((t_token *)(token_list->base.prev))->type == REDIR)
			{
				ft_putstr_fd("Catshell: syntax error near unexpected token `newline'\n", 2);
				return (ERROR);
			}
		}
		token_list = (t_token *)(token_list->base.next);
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
				if ((t_token *)(token_list->base.next) == NULL)
					return (ERROR);
			}
			else if (!ft_strncmp(token_list->value, ">>", 3))
			{
				token_list->type = APPEND;
				((t_token *)(token_list->base.next))->type = OUTFILE;
			}
		}
		token_list = ((t_token *)(token_list->base.next));
	}
	return (0);
}
