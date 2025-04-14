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
		signal_init();
		read_line = readline(PROMPT);
		// if (readline && *readline)
		// {
			add_history(read_line);
			if (start_tokenization(read_line, data) == FAIL)
				continue;
		// }
		execute(data);
		free_lexer(&data->token);
		free_cmd_table(&data->input);
	}
	mega_clean(data);
	return (0);
}
