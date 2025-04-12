#include "../../inc/env.h"

int			set_var(t_env_nodes *new_var, t_env_nodes *env);
static int	is_export_sorted(t_env_nodes *env);

int	create_export(t_struct_ptrs *data)
{
	t_env_nodes	*new_var;

	if (!(data))
		return (FAIL);
	while (is_export_sorted(data->env))
	{
		new_var = malloc(sizeof(t_env_nodes));
		if (!new_var)
			return (FAIL);
		*new_var = (t_env_nodes){0};
		new_var->base.next = NULL;
		if (set_var(new_var, data->env))
			return (free(new_var), error_handling(data), FAIL);
		if (append_node((t_list_base **)&data->export, (t_list_base *)new_var))
			return (free_one_env_node(new_var), FAIL);
	}
	return (SUCCESS);
}

int	set_var(t_env_nodes *new_var, t_env_nodes *env)
{
	t_env_nodes	*smallest;
	t_env_nodes	*curr;

	curr = env;
	smallest = NULL;
	while (curr)
	{
		if ((!smallest || ft_strcmp(curr->var_name, smallest->var_name) < 0)
			&& curr->copied == 0)
			smallest = curr;
		curr = (t_env_nodes *)curr->base.next;
	}
	if (!smallest)
		return (FAIL);
	new_var->var_name = ft_strjoin("declare -x ", smallest->var_name);
	if (!new_var->var_name)
		return (FAIL);
	new_var->var_value = ft_strdup(smallest->var_value);
	if (!new_var->var_value)
		return (free(new_var->var_name), FAIL);
	smallest->copied = 1;
	return (SUCCESS);
}

static int	is_export_sorted(t_env_nodes *env)
{
	t_env_nodes	*curr;

	curr = env;
	while (curr)
	{
		if (curr->copied == 0)
			return (FAIL);
		curr = (t_env_nodes *)curr->base.next;
	}
	return (SUCCESS);
}
