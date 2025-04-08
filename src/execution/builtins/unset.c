#include "../../../inc/execution.h"

int		unset_vars(t_struct_ptrs *data, t_env_nodes **lst_to_unset, int offset);
void	reassign_node_pointers(t_env_nodes **list_root, t_env_nodes *curr);
int		check_match(char *cmd_arg, char *var_name);
int		remove_node(t_env_nodes **lst_to_unset, t_env_nodes *curr);

int	unset(t_struct_ptrs *data)
{
	int			var_unset;

	var_unset = 0;
	if (data->env && unset_vars(data, &data->env, 0))
		var_unset += 1;
	if (data->export && unset_vars(data, &data->export, 11))
		var_unset += 1;
	if (var_unset != 0)
		return (SUCCESS);
	else
		return (FAIL);
}

int	unset_vars(t_struct_ptrs *data, t_env_nodes **lst_to_unset, int offset)	//static or not??
{
	t_env_nodes	*curr;
	t_env_nodes	*next;
	int			i;
	int			removed;

	curr = *lst_to_unset;
	next = NULL;
	removed = 0;
	while (curr)
	{
		next = (t_env_nodes *)curr->base.next;
		i = 0;
		while (data->input->cmd_arr[i])
		{
			if (is_equal_sign_present(data->input->cmd_arr[i]) && !check_match \
				(data->input->cmd_arr[i], (curr->var_name + offset)))
			{
				removed = remove_node(lst_to_unset, curr);
				break ;
			}
			i++;
		}
		curr = next;
	}
	return (removed);
}

int	remove_node(t_env_nodes **lst_to_unset, t_env_nodes *curr)
{
	reassign_node_pointers(lst_to_unset, curr);
	free_one_env_node(curr);
	return (1);
}

void	reassign_node_pointers(t_env_nodes **list_root, t_env_nodes *curr) //static or not??
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
	//int	res;

	//res = 0;
	cmd_arg_len = ft_strlen(cmd_arg);
	var_name_len_w_equal = ft_strlen(var_name);
	var_name_len_wo_equal = ft_strlen(var_name) - 1;
	if (!ft_strncmp(cmd_arg, (var_name), var_name_len_wo_equal) \
		&& (cmd_arg_len == var_name_len_w_equal \
		|| cmd_arg_len == var_name_len_wo_equal))
		return (SUCCESS);
	return (FAIL);
}
