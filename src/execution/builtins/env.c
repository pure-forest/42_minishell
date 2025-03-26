#include "../../../inc/execution.h"

int	env(t_struct_ptrs *data)
{
	t_env_nodes	*curr;

	curr = NULL;
	if (data->env)
	{
		curr = data->env;
		while (curr)
		{
			if (curr->var_value)
				printf("%s%s\n", curr->var_name, curr->var_value);
			else
				printf("%s\n", curr->var_name);
			curr = (t_env_nodes *)curr->base.next;
		}
		return (0);
	}
	return (1);
}
