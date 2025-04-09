#include "../../inc/utils.h"

void	free_lexer(t_token **head)
{
	t_token	*temp;

	if (!(*head))
		return ;
	while ((*head))
	{
		temp = (*head);
		(*head) = (t_token *)(*head)->base.next;
		free(temp->value);
		temp->value = NULL;
		free(temp);
		temp = NULL;
	}
	return ;
}

void	ft_free_double_ptr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
		{
			free(str[i]);
			str[i] = NULL;
		}
		i++;
	}
	free(str);
	str = NULL;
}

void	free_env_nodes(t_env_nodes **root)
{
	t_env_nodes	*tmp;
	t_env_nodes	*curr;

	if (!root || !*root)
		return ;
	curr = *root;
	while (curr)
	{
		tmp = (t_env_nodes *)curr->base.next;
		free(curr->var_name);
		free(curr->var_value);
		free(curr);
		curr = tmp;
	}
	*root = NULL;
}

void	free_one_env_node(t_env_nodes *node_to_free)
{
	free(node_to_free->var_name);
	free(node_to_free->var_value);
	free(node_to_free);
}

void	clean_up_arr(t_struct_ptrs *data)
{
	int	i;

	i = 0;
	if (data->exec_env)
	{
		while(data->exec_env[i])
			free (data->exec_env[i++]);
		free(data->exec_env);
		data->exec_env = NULL;
	}
	return ;
}

void	free_cmd_table(t_input **head)
{
	t_input	*temp;

	if (!(*head))
		return ;
	while ((*head))
	{
		temp = (*head);
		*head = (t_input *)((*head)->base.next);
		if (temp->cmd_arr)
			ft_free_double_ptr(temp->cmd_arr);
		if (temp->redir_in)
			ft_free_double_ptr(temp->redir_in);
		if (temp->redir_out)
			ft_free_double_ptr(temp->redir_out);
		free(temp);
		temp = NULL;
	}
	return ;
}