#include "../../inc/parsing.h"

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

// void	print_double_ptr(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		printf("str[%d] = %s\n", i, str[i]);
// 		i++;
// 	}
// }

void	free_lexer(t_token **head)
{
	t_token	*temp;

	if (!(*head))
		return ;
	while ((*head))
	{
		temp = (*head);
		*head = (*head)->next;
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
