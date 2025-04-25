#include "../inc/minishell.h"

int	main(int argc, char **av, char **envp)
{
	char			*read_line;
	t_struct_ptrs	*data;

	if (!argc || !av)
		return (FAIL);
	data = &((t_struct_ptrs){0});
	if (!IS_OK_TO_RUN(create_env(envp, data)))
		return (FAIL);
	if (!IS_OK_TO_RUN(create_export(data)))
		return (FAIL);
	set_shell_level(data);
	while (1)
	{
		signal_init();
		g_signal_numb = 0;
		read_line = readline(PROMPT);
		if (!read_line)
			break ;
		interupt_input(data);
		add_history(read_line);
		if (start_tokenization(read_line, data) == FAIL)
		{
			free_lexer(&data->token);
			continue ;
		}
		execute(data);
		mini_clean(data);
	}
	mega_clean(data);
	return (0);
}
