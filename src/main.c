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
	signal_init();
	while (1)
	{
		signal_numb = 0;
		read_line = readline(PROMPT);
		if (!read_line)
			break;
		add_history(read_line);
		if (start_tokenization(read_line, data) == FAIL)
			continue;
		execute(data);
		mini_clean(data);
	}
	mega_clean(data);
	return (0);
}
