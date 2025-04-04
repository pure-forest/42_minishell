#include "../../inc/execution.h"

void	error_handling(t_struct_ptrs *data)
{
	if (data->env)
		free_env_nodes(&data->env);
	if (data->export)
		free_env_nodes(&data->export);
	if (data->exec_env)
		clean_up_arr(data);
}

void	free_env_nodes(t_env_nodes **root)
{
	t_env_nodes	*tmp;
	t_env_nodes	*curr;

	if (!root || !*root)
		return ;
	curr = *root;
	while (curr)
	{
		tmp = (t_env_nodes *)curr->base.next;
		free(curr->var_name);
		free(curr->var_value);
		free(curr);
		curr = tmp;
	}
	*root = NULL;
}

void	free_one_env_node(t_env_nodes *node_to_free)
{
	free(node_to_free->var_name);
	free(node_to_free->var_value);
	free(node_to_free);
}

void	clean_up_arr(t_struct_ptrs *data)
{
	int	i;

	i = 0;
	if (data->exec_env)
	{
		while(data->exec_env[i])
			free (data->exec_env[i++]);
		free(data->exec_env);
		data->exec_env = NULL;
	}
	return ;
}