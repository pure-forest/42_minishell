#include "../inc/minishell.h"


int	execute_builtin(t_struct_ptrs *data)
{
	char	*temp;

	temp = data->input->cmd;
	if (!temp)
		return (FAIL);
	if (!ft_strncmp("cd", temp, 2))
		return (cd(data));
	if (!ft_strncmp("echo", temp, 4))
		return (echo(data));
	if (!ft_strncmp("env", temp, 3))
		return (env(data));
	if (!ft_strncmp("export", temp, 6))
		return (export(data));
	if (!ft_strncmp("pwd", temp, 3))
		return (pwd(data));
	if (!ft_strncmp("unset", temp, 5))
		return (unset(data));
	else
		return (FAIL);
}

int	start_tokenization(char *read_line, t_struct_ptrs data)
{
	t_token			*token;
	int				ret_val = 0;

	token = NULL;
	token = lexer(read_line);
	free(read_line);
	if (!token)
		return (ERROR);
	// print_token_list(token);
	data.input = parser(token);
	free_lexer(&token);
	if (!data.input)
		return (ERROR);
	// print_input(data.input);
	printf("\n---------start of program output-----------\n");
	ret_val = execute_builtin(&data);
	printf("---------end of program output-----------\n");
	if (ret_val == FAIL)
	{
		printf("command not found\n");
		return (ERROR);
	}
	free_cmd_table(&data.input);
	return (SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	char			*read_line;
	t_struct_ptrs 	data;

	(void)ac;
	(void)av;

	data = (t_struct_ptrs){0};
	if (create_env(envp, &data))
		return (FAIL);
  	if (create_export(&data))
		return (FAIL);
	while (1)
	{
		read_line = readline(PROMPT);
		if (read_line && *read_line)
			add_history(read_line);
		if (start_tokenization(read_line, data) == ERROR)
			ft_putstr_fd("Error\n", 2);
	}
	free_env_nodes(&data.env);
	free_env_nodes(&data.export);
	return (0);
}
