#include "../../inc/parsing.h"

void	print_input(t_input *head)
{
	int			fix_dis;
	int			fix_dis_index;
	int			i = 0;
	int			node;

	fix_dis_index = 5;
	node = 1;
	fix_dis = 20;
	printf("\n----------start of cmd table--------\n");
	printf("| %-*s | %-*s |\n", fix_dis_index, "index", fix_dis, "cmd args");
	printf("--------------------------------------\n");
	while (head)
	{
		printf("\n-----------node %d--------------\n", node);
		printf("-----------cmd args--------------\n");
		i = 0;
		while (head->cmd_arr[i])
		{
			printf("| %-*d | %-*s |\n", fix_dis_index, i, fix_dis, (head->cmd_arr)[i]);
			i++;
		}
		i = 0;
		printf("-----------redir_in--------------\n");
		while (head->redir_in[i])
		{
			printf("| %-*d | %-*s |\n", fix_dis_index, i, fix_dis, (head->redir_in)[i]);
			i++;
		}
		printf("-----------redir_out--------------\n");
		i  = 0;
		while (head->redir_out[i])
		{
			printf("| %-*d | %-*s |\n", fix_dis_index, i, fix_dis, (head->redir_out)[i]);
			i++;
		}
		printf("append = %d\n", head->append);
		head = (t_input *)(head->base.next);
		node++;
	}
	printf("-----------end of cmd table--------\n");
}
