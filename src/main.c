#include "../inc/minishell.h"


int	execute_builtin(t_struct_ptrs *data)
{
	char	*temp;

	temp = data->input->cmd_arr[0];
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
	// int				ret_val = 0;

	data.token = lexer(read_line);
	// print_token_list(data.token);
	free(read_line);
	if (!data.token)
	{
		printf("lexer failure\n");
		return (FAIL);
	}
	remove_quotes(data.token, &data);
	data.input = parser(&data);
	print_input(data.input);
	if (!data.input)
	{
		printf("parser failure\n");
		return (FAIL);
	}
	// print_input(data.input);

	// printf("\n---------start of program output-----------\n");
	// ret_val = execute_builtin(&data);
	// printf("---------end of program output-----------\n");
	// if (ret_val == FAIL)
	// {
	// 	printf("command not found\n");
	// 	free_cmd_table(&data.input);
	// 	return (FAIL);
	// }
	free_cmd_table(&data.input);
	free_lexer(&data.token);
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
		{
			add_history(read_line);
			if (start_tokenization(read_line, data) == FAIL)
				ft_putstr_fd("Error\n", 2);
		}
		else
			free(read_line);
	}
	free_env_nodes(&data.env);
	free_env_nodes(&data.export);
	return (0);
}
