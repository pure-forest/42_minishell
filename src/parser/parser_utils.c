#include "../../inc/parsing.h"

char	*free_and_join(char *s1, char *s2)
{
	char *temp;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	s1 = NULL;
	s2 = NULL;
	return (temp);
}

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

void	free_cmd_table(t_input **head)
{
	t_input	*temp;

	if (!(*head))
		return ;
	while ((*head))
	{
		temp = (*head);
		*head = (t_input *)((*head)->base.next);
		if (temp->cmd_arr)
			ft_free_double_ptr(temp->cmd_arr);
		if (temp->redir_in)
			ft_free_double_ptr(temp->redir_in);
		if (temp->redir_out)
			ft_free_double_ptr(temp->redir_out);
		free(temp);
		temp = NULL;
	}
	return ;
}

t_input	*cmd_table_init(char **cmd_arr)
{
	t_input	*temp;

	if (!cmd_arr)
		return (NULL);
	temp = ft_calloc(1, sizeof(t_input));
	if (!temp)
		return (NULL);
	temp->cmd_arr = cmd_arr;
	temp->redir_in = NULL;
	temp->redir_out = NULL;
	temp->base.next = NULL;
	temp->base.prev = NULL;
	return (temp);
}
