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
	int		num;
	t_token	*temp;

	num = 0;
	temp = token;
	while (temp)
	{
		if (temp->type == INFILE || temp->type == OUTFILE
			|| temp->type == OUTFILE_APPEN)
			num++;
		if (temp->type == PIPE)
			break ;
		temp = (t_token *)(temp->base.next);
	}
	return (num);
}
