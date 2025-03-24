#include "../../inc/lexer.h"

t_token	*find_last(t_token *root)
{
	if (!root)
		return (NULL);
	while (root->next)
		root = root->next;
	return (root);
}

t_token	*node_init(t_token_type type, char *token_value)
{
	t_token	*node;

	if (!token_value)
		return (NULL);
	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = token_value;
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	append_node(t_token *node, t_token *head)
{
	t_token *last_var;

	last_var = find_last(head);
	if (!last_var)
		return (ERROR);
	last_var->next = node;
	node->prev = last_var;
	return (0);
}

void	print_token_list(t_token *lexer)
{
	int	i;
	int	fix_dis;

	i = 0;
	fix_dis = 10;
	printf("\n-------------start of lexer----------\n");
	printf("| %-*s | %-*s |\n", fix_dis, "token", fix_dis, "toekn type");
	printf("---------------------------\n");
	while (lexer)
	{
		printf("| %-*s | %-*d |\n", fix_dis, lexer->value, fix_dis, lexer->type);
		lexer = lexer->next;
	}
	printf("-------------end of lexer-----------\n\n");
}
