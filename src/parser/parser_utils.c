#include "../../inc/parsing.h"

int	cmd_arr_num(t_token *token_list)
{
	int	num;

	num = 0;
	while (token_list)
	{
		if (token_list->type == PIPE)
			break;
		if (token_list->type == WORD)
			num++;
		token_list = (t_token *)(token_list->base.next);
	}
	return (num);
}

void	get_next_cmd_node(t_token **token_list)
{
	t_token	*temp;

	temp = NULL;
	while ((*token_list))
	{
		if ((*token_list)->type == PIPE)
		{
			temp = (t_token *)(*token_list)->base.next;
			*token_list = temp;
			return ;
		}
		(*token_list) = (t_token *)((*token_list)->base.next);
	}
	return ;
}

int	get_redir_num(t_token *token, t_token_type redir)
{
	int	num;

	num = 0;
	while (token)
	{
		if (token->type == redir)
			num++;
		if (token->type == PIPE)
			break;
		token = (t_token *)(token->base.next);
	}
	return (num);
}

int	is_last_file_append(t_token *token)
{
	int		redir_num;
	int		i;

	redir_num = get_redir_num(token, OUTPUT);
	redir_num += get_redir_num(token, APPEND);
	i = 0;
	while (token && i < redir_num)
	{
		if (token->type == OUTPUT || token->type == APPEND)
			i++;
		token = (t_token *)(token->base.next);
	}
	if ((t_token *)(token->base.prev) &&
		((t_token *)(token->base.prev))->type == APPEND)
		return (YES);
	else
		return (NO);
}
