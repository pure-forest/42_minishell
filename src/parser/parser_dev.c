#include "../../inc/parsing.h"

void	print_input(t_input *head)
{
	int			fix_dis;
	int			fix_dis_index;
	int			i = 0;
	int			node;
	t_redir		*temp;
	t_input		*temp_head;

	fix_dis_index = 5;
	node = 1;
	fix_dis = 20;
	temp_head = head;
	printf("\n----------start of cmd table--------\n");
	printf("| %-*s | %-*s |\n", fix_dis_index, "index", fix_dis, "cmd args");
	printf("--------------------------------------\n");
	while (temp_head)
	{
		temp = temp_head->redirection;
		printf("\n-----------node %d--------------\n", node);
		printf("-----------cmd args--------------\n");
		i = 0;
		while (temp_head->cmd_arr[i])
		{
			printf("| %-*d | %-*s |\n", fix_dis_index, i, fix_dis, (temp_head->cmd_arr)[i]);
			i++;
		}
		i = 0;
		printf("-----------redirections-------------\n");
		while (temp)
		{
			printf("| %-*d | %-*s |\n", fix_dis_index, temp->type, fix_dis,
				temp->file_name);
			temp = (t_redir*)(temp->base.next);
		}
		printf("-----------redirections-------------\n");
		temp_head = (t_input *)(temp_head->base.next);
		node++;
	}
	printf("-----------end of cmd table--------\n");
}
