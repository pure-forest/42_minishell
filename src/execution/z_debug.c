/// DEBUGGGGG DELETE!!!!!!!!!!!


//printf("Before unset_env:\n");
//print_list(data->export);

#include "../../inc/execution.h"

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

//Call like this:
//     print_list((t_list_base *)head, print_inp_node);
void    print_inp_nodes(void *node)
{
	t_input   *inp_node;
	int		i;

	inp_node = (t_input *)node;
	i = -1;
	while (inp_node->token_value[++i])
	{
	   printf("Node at %p | Type: %d | Value[%d]: %s |  Next: %p | Prev: %p\n" ,
			(void *)inp_node, inp_node->token_type, i, inp_node->token_value[i],
			(void *)inp_node->base.next, (void *)inp_node->base.prev);
	}
}
