#include "../../../inc/execution.h"

static int	print_export(t_struct_ptrs *data);
static int	update_export(t_struct_ptrs *data, t_input *curr, int i);
static int	var_fill_export(char *cmd_arr, char *equal_sign, \
							t_env_nodes *new_var);
static void	insert_node(t_env_nodes **export, t_env_nodes *new_var);
t_env_nodes	*find_position(t_env_nodes *root, t_env_nodes *new_var);

int	export(t_struct_ptrs *data, t_input *curr)
{
	int	i;

	i = 0;
	if (!curr->cmd_arr[1])
		return (print_export(data));
	else
	{
		if (update_export(data, curr, i))
			return (FAIL);
		if (update_env(data, curr))
			return (FAIL);
		return (SUCCESS);
	}
}

static int	print_export(t_struct_ptrs *data)
{
	t_env_nodes	*curr;

	curr = NULL;
	if (data->export)
	{
		curr = data->export;
		while (curr)
		{
			if (ft_strncmp(curr->var_name, "declare -x _=", 13))
			{
				if (curr->var_value)
					printf("%s\"%s\"\n", curr->var_name, curr->var_value);
				else
					printf("%s\n", curr->var_name);
			}
			curr = (t_env_nodes *)curr->base.next;
		}
		return (0);
	}
	return (1);
}

static int	update_export(t_struct_ptrs *data, t_input *curr, int i)
{
	t_env_nodes	*new_var;
	char		*equal_sign;
	int			ret_value;

	ret_value = 0;
	while (curr->cmd_arr[++i])
	{
		if (check_export_syntax(curr->cmd_arr[i]))
		{
			print_error("export: `", curr->cmd_arr[i], \
			"': not a valid identifier");
			ret_value = 1;
			continue ;
		}
		equal_sign = ft_strchr(curr->cmd_arr[i], '=');
		new_var = malloc(sizeof(t_env_nodes));
		if (!new_var)
			return (FAIL);
		*new_var = (t_env_nodes){0};
		if (var_fill_export(curr->cmd_arr[i], equal_sign, new_var))
			return (free(new_var), FAIL);
		does_var_exist(&data->export, new_var->var_name);
		insert_node(&data->export, new_var);
	}
	return (ret_value);
}

static int	var_fill_export(char *cmd_arr, char *equal_sign, \
							t_env_nodes *new_var)
{
	char		*tmp;

	if (equal_sign)
	{
		tmp = ft_strndup(cmd_arr, (equal_sign - cmd_arr) + 1);
		if (!tmp)
			return (FAIL);
		new_var->var_name = ft_strjoin("declare -x ", tmp);
		if (!new_var->var_name)
			return (free(tmp), FAIL);
		free(tmp);
		new_var->var_value = ft_strdup(equal_sign + 1);
		if (!new_var->var_value)
			return (free(new_var->var_name), FAIL);
	}
	else
	{
		new_var->var_name = ft_strjoin("declare -x ", cmd_arr);
		if (!new_var->var_name)
			return (FAIL);
	}
	return (SUCCESS);
}

static void	insert_node(t_env_nodes **export, t_env_nodes *new_var)
{
	t_env_nodes	*target;

	target = find_position(*export, new_var);
	if (!target)
	{
		if (!*export)
			*export = new_var;
		else
		{
			new_var->base.next = (t_list_base *)(*export);
			(*export)->base.prev = (t_list_base *)new_var;
			*export = new_var;
		}
	}
	else
	{
		if (target->base.next)
			target->base.next->prev = (t_list_base *)new_var;
		new_var->base.next = target->base.next;
		target->base.next = (t_list_base *)new_var;
		new_var->base.prev = (t_list_base *)target;
	}
}
