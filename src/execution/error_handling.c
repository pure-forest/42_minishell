#include "../../inc/execution.h"

void	error_handling(t_struct_ptrs *data)
{
	if (data->env)
		free_env_nodes(&data->env);
	if (data->export)
		free_env_nodes(&data->export);
	// if (data->exec_env)
	// {
	// 	clean_up_arr(data->exec_env);
	// 	data->exec_env = NULL;
	// }
	// if (data->split_path)
	// {
	// 	clean_up_arr(data->split_path);
	// 	data->split_path = NULL;
	// }

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

void	clean_up_arr(char **arr_ptr)
{
	int	i;

	i = 0;
	if (arr_ptr)
	{
		while(arr_ptr[i])
			free (arr_ptr[i++]);
		free(arr_ptr);
	}
	return ;
}

void	clean_up_exec_creations(t_struct_ptrs *data)
{
	if (data->exec_env)
	{
		clean_up_arr(data->exec_env);
		data->exec_env = NULL;
	}
	if (data->split_path)
	{
		clean_up_arr(data->split_path);
		data->split_path = NULL;
	}
}
