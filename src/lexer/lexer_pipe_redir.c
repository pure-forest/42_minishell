#include "../../inc/lexer.h"

void	push_to_list(t_token_type num, char *value, t_token **head)
{
	t_token	*temp;

	temp = malloc(sizeof(t_token));
	if (!temp)
	{
		return ;
	}
	temp->type = num;
	temp->value = value;
	temp->next = (*head);
	temp->prev = NULL;
	if (*head)
		(*head)->prev = temp;
	(*head) = temp;
}

int	tokenize_pipe(char *str, int *i, t_token **token_list)
{
	char	*token_value;

	if (str[*i] == '|')
	{
		token_value = ft_substr(str, *i, 1);
		if (!token_value)
			return (ERROR);
		push_to_list(PIPE, token_value, token_list);
		(*i)++;
	}
	return (0);
}

int	tokenize_redir(char *str, int *i, t_token **token_list)
{
	char	*token_value;
	int		length;

	length = 1;
	if (str[*i] == '<' || str[*i] == '>')
	{
		if (str[*i] == str[*i + 1])
			length++;
		token_value = ft_substr(str, *i, length);
		if (!token_value)
			return (ERROR);
		push_to_list(REDIR, token_value, token_list);
		*i += length;
	}
	return (0);
}
