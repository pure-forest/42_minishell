#include "../../inc/utils.h"

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

void	clean_up_temp_files(void)
{
	int		index;
	char	*index_str;
	char	*file_name;

	index = 0;
	index_str = ft_itoa(index);
	if (!index_str)
		return ;
	file_name = ft_strjoin(HEREDOC_TEMP_NAME, index_str);
	while (access(file_name, F_OK) == 0)
	{
		unlink(file_name);
		free(index_str);
		free(file_name);
		index++;
		index_str = ft_itoa(index);
		if (!index_str)
			return ;
		file_name = ft_strjoin(HEREDOC_TEMP_NAME, index_str);
	}
	free(file_name);
	free(index_str);
	file_name = NULL;
	return ;
}

void	mega_clean(t_struct_ptrs *data)
{
	rl_clear_history();
	free_lexer(&data->token);
	free_cmd_table(&data->input);
	free_env_nodes(&data->env);
	free_env_nodes(&data->export);
	clean_up_arr(data);
	clean_up_temp_files();
	return ;
}
