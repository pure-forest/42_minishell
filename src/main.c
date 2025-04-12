#include "../inc/minishell.h"

int	main(int argc, char **av, char **envp)
{
	char			*read_line;
	t_struct_ptrs 	*data;

	if (!argc || !av || !*envp)
		return (FAIL);
	data = &((t_struct_ptrs ){0});
	if (create_env(envp, data))
		return (FAIL);
  	if (create_export(data))
		return (FAIL);
	while (1)
	{
		read_line = readline(PROMPT);
		add_history(read_line);
		if (!ft_strncmp(read_line, "exit", 4))
			exit(0);
		if (start_tokenization(read_line, data) == FAIL)
			continue;
		launch_builtin(data);
		free_lexer(&data->token);
		free_cmd_table(&data->input);
	}
	clean_up_arr(data);
	return (0);
}
