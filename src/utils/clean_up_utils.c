#include "../../inc/utils.h"

// static void	loop_clean_temp_files(char **file_name, char **index_str,
// 				int *index);

// void	clean_up_temp_files(t_input **input)
// {
// 	char	**infile;
// 	t_input	*node;

// 	node = *input;
// 	while (node)
// 	{
// 		if ()
// 	}
// 	infile = (*input)->redir_in;
// 	delete_temp_files(infile);

// 	return ;
// }

// void	delete_temp_files(char **infile)
// {
// 	int	i;

// 	i = 0;
// 	while (infile[i])
// 	{
// 		if (!ft_strncmp(infile, HEREDOC_TEMP_NAME, 14))
// 			unlink(infile[i]);
// 		i++;
// 	}
// 	return ;
// }

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
	// clean_up_temp_files(&data->input);
	return ;
}

void	mini_clean(t_struct_ptrs *data)
{
	if (data->token)
		free_lexer(&data->token);
	if (data->input)
		free_cmd_table(&data->input);
	return ;
}
