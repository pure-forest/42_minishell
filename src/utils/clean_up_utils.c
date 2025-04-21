#include "../../inc/utils.h"

static void	delete_temp_files_in_node(t_redir *redirection);
static void	clean_up_temp_files(t_input **input);

void	mega_clean(t_struct_ptrs *data)
{
	rl_clear_history();
	if (data->token)
		free_lexer(&data->token);
	if (data->input)
		free_cmd_table(&data->input);
	if (data->env)
		free_env_nodes(&data->env);
	if (data->export)
		free_env_nodes(&data->export);
	error_handling(data);
	return ;
}

void	mini_clean(t_struct_ptrs *data)
{
	if (data->token)
		free_lexer(&data->token);
	if (data->input->redirection)
		clean_up_temp_files(&data->input);
	if (data->input)
		free_cmd_table(&data->input);
	return ;
}

static void	clean_up_temp_files(t_input **input)
{
	t_input	*node;

	node = *input;
	while (node)
	{
		if (node->redirection)
			delete_temp_files_in_node(node->redirection);
		node = (t_input *)(node->base.next);
	}
	return ;
}

static void	delete_temp_files_in_node(t_redir *redirection)
{
	// int		i;
	t_redir	*temp;

	// i = 0;
	temp = redirection;
	while (temp)
	{
		if (!ft_strncmp(temp->file_name, HEREDOC_TEMP_NAME, 14))
			unlink(temp->file_name);
		temp = (t_redir *)(temp->base.next);
	}
	return ;
}
