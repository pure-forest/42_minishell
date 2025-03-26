#include "../../../inc/execution.h"

int		unset_vars(t_struct_ptrs *data, t_env_nodes **lst_to_unset, int offset);
void	reassign_node_pointers(t_env_nodes **list_root, t_env_nodes *curr);

int	unset(t_struct_ptrs *data)
{
	int			var_unset;

	var_unset = 0;
	if (data->env && unset_vars(data, &data->env, 0))
		var_unset += 1;
	if (data->export && unset_vars(data, &data->export, 11))
		var_unset += 1;
	if (var_unset != 0)
		return (0);
	else
		return (1);
}

int	unset_vars(t_struct_ptrs *data, t_env_nodes **lst_to_unset, int offset) //static or not??
{
	t_env_nodes	*curr;
	t_env_nodes	*next;
	int			i;

	curr = *list_to_unset;
	next = NULL;
	while (curr)
	{
		next = (t_env_nodes *)curr->base.next;
		i = 0;
		while (data->input->cmd_arr[++i])
		{
			if (!ft_strncmp(data->input->cmd_arr[i], (curr->var_name + offset), \
			ft_strlen(curr->var_name + offset) - 1) && \
			ft_strlen(data->input->cmd_arr[i]) == \
			ft_strlen(curr->var_name + offset) - 1)
			{
				reassign_node_pointers(list_to_unset, curr);
				free_one_env_node(curr);
				break ;
			}
		}
		curr = next;
	}
	return (0);
}

void	reassign_node_pointers(t_env_nodes **list_root, t_env_nodes *curr) //static or not??
{
	if (curr->base.prev && curr->base.next)
	{
		curr->base.prev->next = curr->base.next;
		curr->base.next->prev = curr->base.prev;
	}
	else if (!curr->base.prev && curr->base.next)
	{
		*list_root = (t_env_nodes *)curr->base.next;
		curr->base.next->prev = curr->base.prev;
	}
	else if (curr->base.prev && !curr->base.next)
		curr->base.prev->next = NULL;
}
