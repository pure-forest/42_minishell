#include "../../inc/utils.h"

void	error_handling(t_struct_ptrs *data)
{
	if (data->env)
		free_env_nodes(&data->env);
	if (data->export)
		free_env_nodes(&data->export);
	if (data->exec_env)
		clean_up_arr(data);
}