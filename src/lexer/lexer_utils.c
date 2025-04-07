#include "../../inc/lexer.h"

t_token	*token_init(t_token_type type, char *token_value)
{
	t_token	*node;

	if (!token_value)
		return (NULL);
	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = token_value;
	node->quote_count = 0;
	node->should_expand = YES;
	node->type = type;
	node->base.next = NULL;
	node->base.prev = NULL;
	return (node);
}

void	print_token_list(t_token *lexer)
{
	int	fix_dis;

	fix_dis = 21;
	printf("\n-----------------start of lexer------------------\n");
	printf("| %-*s | %-*s |\n", fix_dis, "token value", fix_dis, "token type");
	printf("+-----------------------------------------------+\n");
	while (lexer)
	{
		printf("| %-*s | %-*d |\n", fix_dis, lexer->value, fix_dis, lexer->type);
		lexer = (t_token *)(lexer->base.next);
	}
	printf("-----------------end of lexer--------------------\n\n");
}

void	free_lexer(t_token **head)
{
	t_token	*temp;

	if (!(*head))
		return ;
	while ((*head))
	{
		temp = (*head);
		(*head) = (t_token *)(*head)->base.next;
		free(temp->value);
		temp->value = NULL;
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

void	print_double_ptr(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		printf("str[%d] = %s\n", i, str[i]);
		i++;
	}
}
