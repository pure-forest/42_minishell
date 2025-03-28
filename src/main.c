#include "../inc/minishell.h"


int	execute_builtin(t_struct_ptrs *data)
{
	char	*temp;

	temp = data->input->cmd;
	if (!temp)
		return (FAIL);
	if (!ft_strncmp("cd", temp, 2))
		return (cd(data));
	else if (!ft_strncmp("echo", temp, 4))
		return (echo(data));
	else if (!ft_strncmp("env", temp, 3))
		return (env(data));
	else if (!ft_strncmp("export", temp, 6))
		return (export(data));
	else if (!ft_strncmp("pwd", temp, 3))
		return (pwd(data));
	else if (!ft_strncmp("unset", temp, 5))
		return (unset(data));
	else
		return (FAIL);
}

int	main(int ac, char **av, char **envp)
{
	char			*read_line;
	t_struct_ptrs 	data;
	t_token			*token;
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
		token = lexer(read_line);
		free(read_line);
		if (token)
			print_token_list(token);
		data.input = parser(token);
		free_lexer(&token);
		if (data.input)
			print_input(data.input);
		printf("\n---------start of program output-----------\n");
		ret_val = execute_builtin(&data);
		printf("---------end of program output-----------\n");
		if (ret_val == FAIL)
			printf("command not found\n");
		free_cmd_table(&data.input);
		free_env_nodes(&data.env);
		free_env_nodes(&data.export);
	}
	return (0);
}
