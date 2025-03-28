#include "../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char			*read_line;
	t_struct_ptrs 	data;
	t_token			*token;
	t_cmd_table 	*cmd;
	int				ret_val = 0;

	(void)ac;
	(void)av;
	token = NULL;
	data = (t_struct_ptrs){0};
	while (1)
	{
		read_line = readline(PROMPT);
		if (create_env(envp, &data))
			return (FAIL);
  		if (create_export(&data))
	  		return (FAIL);
		if (read_line && *read_line)
			add_history(read_line);
		if (read_line)
		{
			token = lexer(read_line);
			free(read_line);
		}
		// if (token)
		// 	print_token_list(token);
		cmd = parser(token);
		data.input = get_cmd_table(cmd);
		ret_val = echo(&data);
		if (ret_val == -1)
			printf("Error\n");
		free_lexer(&token);
	}
	return (0);
}
