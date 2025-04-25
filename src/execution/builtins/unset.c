#include "../../../inc/execution.h"

static int	unset_vars(t_input *curr, t_env_nodes **lst_to_unset, int offset);
static void	reassign_node_pointers(t_env_nodes **list_root, t_env_nodes *curr);

int	unset(t_struct_ptrs *data, t_input *curr)
{
	int			env_unset;
	int			export_unset;

	env_unset = EMPTY;
	export_unset = EMPTY;
	if (data->env)
		env_unset = unset_vars(curr, &data->env, 0);
	if (data->export)
		export_unset = unset_vars(curr, &data->export, 11);
	if ((env_unset == YES || env_unset == NOT_FOUND || env_unset == EMPTY) \
		|| (export_unset == YES || export_unset == NOT_FOUND \
		|| export_unset == EMPTY))
		return (SUCCESS);
	else
		return (0);
}

static int	unset_vars(t_input *curr, t_env_nodes **lst_to_unset, int offset)
{
	t_env_nodes	*list;
	t_env_nodes	*next;
	int			i;
	int			removed;

	list = *lst_to_unset;
	next = NULL;
	removed = NOT_FOUND;
	while (list)
	{
		next = (t_env_nodes *)list->base.next;
		i = 0;
		while (curr->cmd_arr[++i])
		{
			if (is_equal_sign_present(curr->cmd_arr[i]) && !check_match \
				(curr->cmd_arr[i], (list->var_name + offset)))
			{
				removed = remove_node(lst_to_unset, list);
				break ;
			}
		}
		list = next;
	}
	return (removed);
}

int	remove_node(t_env_nodes **lst_to_unset, t_env_nodes *curr)
{
	reassign_node_pointers(lst_to_unset, curr);
	free_one_env_node(curr);
	return (1);
}

static void	reassign_node_pointers(t_env_nodes **list_root, t_env_nodes *curr)
{
	if (!curr->base.prev && !curr->base.next)
		*list_root = NULL;
	if (curr->base.prev && curr->base.next)
	{
		curr->base.prev->next = curr->base.next;
		curr->base.next->prev = curr->base.prev;
	}
	else if (!curr->base.prev && curr->base.next)
	{
		*list_root = (t_env_nodes *)curr->base.next;
		curr->base.next->prev = curr->base.prev;
	}
	else if (curr->base.prev && !curr->base.next)
		curr->base.prev->next = NULL;
}

int	check_match(char *cmd_arg, char *var_name)
{
	int	cmd_arg_len;
	int	var_name_len_w_equal;
	int	var_name_len_wo_equal;

	cmd_arg_len = ft_strlen(cmd_arg);
	var_name_len_w_equal = ft_strlen(var_name);
	var_name_len_wo_equal = ft_strlen(var_name) - 1;
	if (!ft_strncmp(cmd_arg, (var_name), var_name_len_wo_equal) \
		&& (cmd_arg_len == var_name_len_w_equal \
		|| cmd_arg_len == var_name_len_wo_equal))
		return (SUCCESS);
	return (FAIL);
}
