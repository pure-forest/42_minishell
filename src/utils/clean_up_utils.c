#include "../../inc/utils.h"

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
	error_handling(data);
	clean_up_temp_files();
	return ;
}

void	mini_clean(t_struct_ptrs *data)
{
	free_lexer(&data->token);
	free_cmd_table(&data->input);
	return ;
}
