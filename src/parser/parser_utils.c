#include "../../inc/parsing.h"

int	cmd_arr_num(t_token *token_list)
{
	int	num;

	num = 0;
	while (token_list)
	{
		if (token_list->type == PIPE)
			break ;
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

int	get_redir_num(t_token *token)
{
	int	num;

	num = 0;
	while (token)
	{
		if (token->type == INFILE || token->type == OUTFILE
			|| token->type == OUTFILE_APPEN)
			num++;
		if (token->type == PIPE)
			break ;
		token = (t_token *)(token->base.next);
	}
	return (num);
}
