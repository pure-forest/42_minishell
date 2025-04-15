#include "../../inc/lexer.h"

static int	replace_unclose_pipe(t_token *node, t_struct_ptrs *data);

int	check_redir_file(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == REDIR)
		{
			if (token_list->base.next == NULL
				|| ((t_token *)(token_list->base.next))->type == REDIR)
			{
				ft_putstr_fd("syntax FAIL near unexpected token `newline'\n",
					2);
				return (FAIL);
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

int	check_pipe(t_token *token_list, t_struct_ptrs *data)
{
	while (token_list)
	{
		if (token_list->type == PIPE && (t_token *)(token_list->base.next))
		{
			if ((t_token *)(token_list->base.prev) == NULL
				|| ((t_token *)(token_list->base.next))->type == PIPE)
			{
				ft_putstr_fd("syntax FAIL near unexpected token `|'\n",
					2);
				return (FAIL);
			}
			if (((t_token *)(token_list->base.prev))->type == REDIR)
			{
				ft_putstr_fd("syntax FAIL near unexpected token`newline'\n",
					2);
				return (FAIL);
			}
		}
		if (token_list->type == PIPE
			&& (t_token *)(token_list->base.next) == NULL)
			if (replace_unclose_pipe(token_list, data) == FAIL)
				return (FAIL);
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
			if (!ft_strncmp(token_list->value, "<<", 2))
			{
				token_list->type = HEREDOC;
				((t_token *)(token_list->base.next))->should_expand = NO;
				if ((t_token *)(token_list->base.next) == NULL)
					return (FAIL);
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

static int	replace_unclose_pipe(t_token *node, t_struct_ptrs *data)
{
	char	*str;
	int		i;

	str = readline("> ");
	i = 0;
	if (!str)
		return (FAIL);
	if (check_for_expansion(data, &str) == FAIL)
		return (FAIL);
	while (str[i])
	{
		if (tokenize_pipe(str, &i, &node) == FAIL)
			break ;
		if (tokenize_redir(str, &i, &node) == FAIL)
			break ;
		if (tokenize_text(str, &i, &node) == FAIL)
			break ;
		while (str && str[i] && ft_strchr(FT_SPACE, str[i]))
			i++;
	}
	if (str[i] != '\0')
		return (FAIL);
	return (SUCCESS);
}
