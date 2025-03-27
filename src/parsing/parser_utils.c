#include "../../inc/parsing.h"

void	free_cmd_table(t_cmd_table **head)
{
	t_cmd_table	*temp;

	if (!(*head))
		return ;
	while ((*head))
	{
		temp = (*head);
		*head = (t_cmd_table *)((*head)->next);
		if (temp->cmd_args)
			ft_free_double_ptr(temp->cmd_args);
		if (temp->cmd)
		{
			free(temp->cmd);
			temp->cmd = NULL;
		}
		free(temp);
		temp = NULL;
	}
	return ;
}

void	print_cmd_table(t_cmd_table *head)
{
	int			fix_dis;
	int			fix_dis_index;
	int			i = 0;

	fix_dis_index = 5;
	fix_dis = 20;
	printf("\n----------start of cmd table--------\n");
	printf("| %-*s | %-*s |\n", fix_dis_index, "index", fix_dis, "cmd args");
	printf("--------------------------------------\n");
	while (head->cmd_args[i])
	{
		printf("| %-*d | %-*s |\n", fix_dis_index, i, fix_dis, (head->cmd_args)[i]);
		i++;
	}
	printf("\n-----------end of cmd table--------\n");
}
