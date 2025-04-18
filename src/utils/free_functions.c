#include "../../inc/utils.h"

void	free_lexer(t_token **head)
{
	t_token	*temp;

	if (!(*head))
		return ;
	while ((*head))
	{
		temp = (*head);
		(*head) = (t_token *)(*head)->base.next;
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		free(temp);
		temp = NULL;
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

void	ft_free_double_ptr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
		{
			free(str[i]);
			str[i] = NULL;
		}
		i++;
	}
	free(str);
	str = NULL;
}
