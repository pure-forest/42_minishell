#include "../inc/minishell.h"

int	main(void)
{
	char		*read_line;
	t_token		*token;
	t_cmd_table	*cmd_table;

	token = NULL;
	cmd_table = NULL;
	while (1)
	{
		read_line = readline(PROMPT);
		if (read_line && *read_line)
			add_history(read_line);
		if (read_line)
		{
			token = lexer(read_line);
			free(read_line);
		}
		if (token)
			print_token_list(token);
		cmd_table = parser(token);
		if (cmd_table)
			print_cmd_table(cmd_table);
		free_lexer(&token);
		free_cmd_table(&cmd_table);
	}
	return (0);
}
