#include "../../inc/lexer.h"

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
