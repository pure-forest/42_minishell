#include "../../inc/env.h"

int	change_var_value(t_env_nodes *list, char *var_to_change, char *new_value, \
	int offset);

char	*get_var_value(t_env_nodes *list, char *var)
{
	t_env_nodes	*curr;

	curr = list;
	if (curr)
	{
		while (curr)
		{
			if (!ft_strncmp(var, curr->var_name, ft_strlen(var)))
				return (curr->var_value);
			curr = (t_env_nodes *)curr->base.next;
		}
	}
	return (NULL);
}

void	update_var_in_both(t_env_nodes *env, t_env_nodes *export, \
							char *var_to_change, char *new_value)
{
	int	var_name_offset;

	var_name_offset = 0;
	change_var_value(env, var_to_change, new_value, var_name_offset);
	var_name_offset = 11;
	change_var_value(export, var_to_change, new_value, var_name_offset);
}

int	change_var_value(t_env_nodes *list, char *var_to_change, char *new_value, \
					int offset)	// does this have to be an int? will i need to check if a var got changed/found in future? static or not??
{
	t_env_nodes	*curr;

	curr = list;
	if (curr)
	{
		while (curr)
		{
			if (!ft_strcmp(var_to_change, (curr->var_name + offset)))
			{
				free (curr->var_value);
				curr->var_value = NULL;
				if (new_value)
				{
					curr->var_value = ft_strdup(new_value);
					if (!curr->var_value)
						return (FAIL);
				}
				else
					return (FAIL);
			}
			curr = (t_env_nodes *)curr->base.next;
		}
	}
	return (FAIL);
}
