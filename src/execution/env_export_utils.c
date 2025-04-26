#include "../../inc/execution.h"

int	change_var_value(t_env_nodes *list, char *var_to_change, char *new_value,
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

void	update_var_in_both(t_env_nodes *env, t_env_nodes *export,
		char *var_to_change, char *new_value)
{
	int	var_name_offset;

	var_name_offset = 0;
	change_var_value(env, var_to_change, new_value, var_name_offset);
	var_name_offset = 11;
	change_var_value(export, var_to_change, new_value, var_name_offset);
}

int	change_var_value(t_env_nodes *list, char *var_to_change, char *new_value,
					int offset)
{
	t_env_nodes	*curr;

	curr = list;
	if (curr)
	{
		while (curr)
		{
			if (!ft_strcmp(var_to_change, (curr->var_name + offset)))
			{
				free(curr->var_value);
				curr->var_value = NULL;
				if (new_value)
				{
					curr->var_value = ft_strdup(new_value);
					if (!curr->var_value)
						return (FAIL);
					return (SUCCESS);
				}
				else
					return (FAIL);
			}
			curr = (t_env_nodes *)curr->base.next;
		}
	}
	return (FAIL);
}

void	set_shell_level(t_struct_ptrs *data)
{
	char	*shlvl_var_value;
	long	shlvl;
	char	*new_value;

	shlvl_var_value = get_var_value(data->env, "SHLVL=");
	if (!shlvl_var_value)
		return (create_var_env_and_export(data, "SHLVL=", "1"));
	if (is_valid_numeric_input(shlvl_var_value) == NO)
		return ;
	shlvl = ft_atol(shlvl_var_value);
	if (shlvl >= 999 || shlvl < 0)
	{
		print_error("warning: shell level (", shlvl_var_value, ") \
		too high or too low, resetting to 1");
		shlvl = 1;
	}
	else
		shlvl++;
	new_value = ft_itoa(shlvl);
	if (!new_value)
		return ;
	update_var_in_both(data->env, data->export, "SHLVL=", new_value);
	return (free(new_value), (void)01);
}

void	create_var_env_and_export(t_struct_ptrs *data, char *var_name,
									char *var_value)
{
	t_input	*var;

	var = malloc(sizeof(t_input));
	var->cmd_arr = malloc(sizeof(char *) * 3);
	var->cmd_arr[0] = "export";
	var->cmd_arr[1] = ft_strjoin(var_name, var_value);
	if (!var->cmd_arr[1])
		return (free(var->cmd_arr), free(var), (void)0);
	var->cmd_arr[2] = NULL;
	export(data, var);
	free(var->cmd_arr[1]);
	free(var->cmd_arr);
	free(var);
}
