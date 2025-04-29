/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_reprocess_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:15:43 by ydeng             #+#    #+#             */
/*   Updated: 2025/04/29 08:13:15 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

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

int	check_pipe(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == PIPE && (t_token *)(token_list->base.next))
		{
			if ((t_token *)(token_list->base.prev) == NULL
				|| ((t_token *)(token_list->base.next))->type == PIPE)
			{
				ft_putstr_fd("syntax FAIL near unexpected token `|'\n", 2);
				return (FAIL);
			}
			if (((t_token *)(token_list->base.prev))->type == REDIR)
			{
				ft_putstr_fd("syntax FAIL near unexpected token`newline'\n", 2);
				return (FAIL);
			}
		}
		if (token_list->type == PIPE
			&& (t_token *)(token_list->base.next) == NULL)
		{
			ft_putstr_fd("syntax FAIL near unexpected token`|'\n", 2);
			return (FAIL);
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
				((t_token *)(token_list->base.next))->type = OUTFILE_APPEN;
			}
		}
		token_list = ((t_token *)(token_list->base.next));
	}
	return (0);
}
