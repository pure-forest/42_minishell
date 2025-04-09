#include "../inc/minishell.h"

static int	execute_builtin(t_struct_ptrs *data);

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
			if (start_tokenization(read_line, data) == FAIL)
				continue;
			execute_builtin(data);
		}
		else
			free(read_line);
	}
	free_env_nodes(&data->env);
	free_env_nodes(&data->export);
	return (0);
}

static int	execute_builtin(t_struct_ptrs *data)
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
