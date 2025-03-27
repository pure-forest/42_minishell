#include "../../../inc/execution.h"

int			print_export(t_struct_ptrs *data);
int			update_export(t_struct_ptrs *data);
int			var_fill(char *cmd_arr, char *equal_sign, t_env_nodes *new_var);
void		insert_node(t_env_nodes **export, t_env_nodes *new_var);
t_env_nodes	*find_position(t_env_nodes *root, t_env_nodes *new_var);

int	export(t_struct_ptrs *data)
{
	//if (!data->input->cmd_arr[1])
	if (!data->input || !data->input->cmd_arr[1]) //this is for test, case where export gets called before data input cmdarr is populated isnt present in mini right?
		return (print_export(data));
	else
	{
		if (update_export(data))
			return (FAIL);
		if (update_env(data))
			return (FAIL);
		return (SUCCESS);
	}
}

int	print_export(t_struct_ptrs *data)
{
	t_env_nodes	*curr;

	curr = NULL;
	if (data->export)
	{
		curr = data->export;
		while (curr)
		{
			if (ft_strncmp(curr->var_name, "declare -x _=", 13)) //ask about this, is it true that export doesnt print the _=?
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

int	update_export(t_struct_ptrs *data)
{
	t_env_nodes	*new_var;
	char		*equal_sign;
	int			i;

	i = 0;
	while (data->input->cmd_arr[++i])
	{
		equal_sign = ft_strchr(data->input->cmd_arr[i], '='); //qnd faccio x env posso mettere check se non c'e l'equal allora vai al prossimo arg
		new_var = malloc(sizeof(t_env_nodes));
		if (!new_var)
			return (FAIL);
		*new_var = (t_env_nodes){0};
		if (var_fill(data->input->cmd_arr[i], equal_sign, new_var))
			return (free(new_var), FAIL);
		insert_node(&data->export, new_var);
	}
	return (SUCCESS);
}

int	var_fill(char *cmd_arr, char *equal_sign, t_env_nodes *new_var)
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

void	insert_node(t_env_nodes **export, t_env_nodes *new_var)
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
