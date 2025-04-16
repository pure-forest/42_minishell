#include "../../../inc/execution.h"

int	var_fill_env(char *cmd_arr, char *equal_sign, t_env_nodes *new_var);

t_env_nodes	*find_position(t_env_nodes *root, t_env_nodes *new_var)
{
	t_env_nodes	*curr;
	t_env_nodes	*smallest;

	if (!root)
		return (NULL);
	curr = root;
	smallest = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->var_name, new_var->var_name) < 0)
			smallest = curr;
		curr = (t_env_nodes *)curr->base.next;
	}
	if (!smallest)
		return (NULL);
	return (smallest);
}

int	update_env(t_struct_ptrs *data, t_input *curr)
{
	t_env_nodes	*new_var;
	char		*equal_sign;
	int			i;

	i = 0;
	while (curr->cmd_arr[++i])
	{
		if (check_export_syntax(curr->cmd_arr[i]))
			continue ;
		equal_sign = ft_strchr(curr->cmd_arr[i], '=');
		if (!equal_sign)
			continue ;
		new_var = malloc(sizeof(t_env_nodes));
		if (!new_var)
			return (FAIL);
		*new_var = (t_env_nodes){0};
		if (var_fill_env(curr->cmd_arr[i], equal_sign, new_var))
			return (free(new_var), FAIL);
		does_var_exist(&data->env, new_var->var_name);
		append_node((t_list_base **)&data->env, (t_list_base *)new_var);
	}
	return (SUCCESS);
}

int	var_fill_env(char *cmd_arr, char *equal_sign, t_env_nodes *new_var)
{
	new_var->var_name = ft_strndup(cmd_arr, (equal_sign - cmd_arr) + 1);
	if (!new_var->var_name)
		return (FAIL);
	new_var->var_value = ft_strdup(equal_sign + 1);
	if (!new_var->var_value)
		return (free(new_var->var_name), FAIL);
	return (SUCCESS);
}

void	does_var_exist(t_env_nodes **list, char *arg)
{
	t_env_nodes	*curr;
	t_env_nodes	*next;

	curr = *list;
	while (curr)
	{
		next = (t_env_nodes *)curr->base.next;
		if (!check_match(curr->var_name, arg))
		{
			remove_node(list, curr);
			break ;
		}
		curr = next;
	}
}

int	check_export_syntax(char *arg)
{
	int	i;
	int	j;

	if (!arg || !arg[0])
		return (EMPTY);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (FAIL);
	if (arg[0] == '_' && !arg[1])
		return (FAIL);
	j = 1;
	while (j < i)
	{
		if (!ft_isalnum(arg[j]) && arg[j] != '_')
			return (FAIL);
		j++;
	}
	return (SUCCESS);
}
