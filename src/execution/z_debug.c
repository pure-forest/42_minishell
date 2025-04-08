/// DEBUGGGGG DELETE!!!!!!!!!!!


//printf("Before unset_env:\n");
//print_list(data->export);

#include "../../inc/execution.h"

void	print_cmd_arr(char **cmd_arr)
{
	int	i;

	i = 0;
	while (cmd_arr[i])
	{
		printf("Arr[%d]: '%s'\n", i, cmd_arr[i]);
		i++;
	}
}

void    print_list(t_list_base *head, void (*print_node)(void *))
{
	t_list_base *curr = head;
	while (curr)
	{
		print_node(curr);
		curr = curr->next;
	}
}

//Call like this:
//     print_list((t_list_base *)head, print_env_nodes);
void    print_env_nodes(void *node)
{
	t_env_nodes *env_node;

	env_node = (t_env_nodes *)node;
	printf("Node at %p | Name: %s | Next: %p | Prev: %p\n",
		   (void *)env_node, env_node->var_name,
		   (void *)env_node->base.next, (void *)env_node->base.prev);
}

// Call like this:
//     print_list((t_list_base *)head, print_inp_node);
void    print_inp_nodes(void *node)
{
	t_input   *inp_node;

	inp_node = (t_input *)node;
	printf("Node at %p |  Next: %p | Prev: %p\n" ,
			(void *)inp_node,
			(void *)inp_node->base.next, (void *)inp_node->base.prev);
	int i = -1;
	while (inp_node->cmd_arr[++i])
		printf("Index[%d]: '%s'\n", i, inp_node->cmd_arr[i]);
	char	**redir = inp_node->redir_in;
	i = -1;
	while (redir[++i])
		printf("Redir_in[%d]:  Value: %s\n", i, redir[i]);
	i = -1;
	redir = inp_node->redir_out;
	while (redir[++i])
		printf("Redir_out[%d]:  Value: %s\n", i, redir[i]);
}
