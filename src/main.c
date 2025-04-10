#include "../inc/minishell.h"

int	main(int argc, char **av, char **envp)
{
	char			*read_line;
	t_struct_ptrs 	*data;

	(void)argc;
	(void)av;
	data = &((t_struct_ptrs ){0});
	if (create_env(envp, data))
		return (FAIL);
  	if (create_export(data))
		return (FAIL);
	while (1)
	{
		read_line = readline(PROMPT);
		if (read_line && *read_line)
		{
			add_history(read_line);
			if (!ft_strncmp(read_line, "exit", 4))
				exit(0);
			if (start_tokenization(read_line, data) == FAIL)
				continue;
			launch_builtin(data);
			free_lexer(&data->token);
			free_cmd_table(&data->input);
		}
		else
			free(read_line);
	}
	free_env_nodes(&data->env);
	free_env_nodes(&data->export);
	return (0);
}
