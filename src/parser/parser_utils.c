#include "../../inc/parsing.h"

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

t_input	*cmd_table_init(char **cmd_arr)
{
	t_input	*temp;

	if (!cmd_arr)
		return (NULL);
	temp = ft_calloc(1, sizeof(t_input));
	if (!temp)
		return (NULL);
	temp->cmd_arr = cmd_arr;
	temp->cmd = ft_strdup(cmd_arr[0]);
	temp->base.next = NULL;
	temp->base.prev = NULL;
	return (temp);
}

void	print_input(t_input *head)
{
	int			fix_dis;
	int			fix_dis_index;
	int			i = 0;

	fix_dis_index = 5;
	fix_dis = 20;
	printf("\n----------start of cmd table--------\n");
	printf("| %-*s | %-*s |\n", fix_dis_index, "index", fix_dis, "cmd args");
	printf("--------------------------------------\n");
	while (head->cmd_arr[i])
	{
		printf("| %-*d | %-*s |\n", fix_dis_index, i, fix_dis, (head->cmd_arr)[i]);
		i++;
	}
	printf("-----------end of cmd table--------\n");
}
