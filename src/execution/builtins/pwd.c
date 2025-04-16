#include "../../../inc/execution.h"

int	pwd(t_struct_ptrs *data)
{
	t_env_nodes	*curr;

	curr = NULL;
	if (data->env)
	{
		curr = data->env;
		while (curr)
		{
			if (!(ft_strncmp(curr->var_name, "PWD=", 4)))
				return (printf("%s\n", curr->var_value), SUCCESS);
			curr = (t_env_nodes *)curr->base.next;
		}
		return (FAIL);
	}
	return (EMPTY);
}
