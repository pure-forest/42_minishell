#include "../../inc/execution.h"
#include <errno.h>

static int	allocate_env_arr(t_struct_ptrs *data, t_env_nodes *env, int amount);

int	is_builtin(t_input *curr)
{
	if (curr->cmd_arr && curr->cmd_arr[0])
	{
		if (!ft_strcmp(curr->cmd_arr[0], "cd") || !ft_strcmp(curr->cmd_arr[0],
				"echo") || !ft_strcmp(curr->cmd_arr[0], "env")
			|| !ft_strcmp(curr->cmd_arr[0], "export")
			|| !ft_strcmp(curr->cmd_arr[0], "pwd")
			|| !ft_strcmp(curr->cmd_arr[0], "unset")
			|| !ft_strcmp(curr->cmd_arr[0], "exit"))
			return (YES);
	}
	return (NO);
}

void	launch_builtin(t_struct_ptrs *data, t_input *curr,
		t_exec_data *exec_data)
{
	char	*cmd;
	int		res;

	cmd = curr->cmd_arr[0];
	if (!ft_strcmp(cmd, "cd"))
		res = cd(data, curr);
	if (!ft_strcmp(cmd, "echo"))
		res = echo(curr);
	if (!ft_strcmp(cmd, "env"))
		res = env(data);
	if (!ft_strcmp(cmd, "export"))
		res = export(data, curr);
	if (!ft_strcmp(cmd, "pwd"))
		res = pwd(data);
	if (!ft_strcmp(cmd, "unset"))
		res = unset(data, curr);
	if (!ft_strcmp(cmd, "exit"))
		res = ft_exit(data, curr, exec_data);
	data->exit_code = res;
}

int	create_execute_env(t_struct_ptrs *data)
{
	t_env_nodes	*curr;
	int			amount;

	if (!data->env)
		return (EMPTY);
	curr = data->env;
	amount = 0;
	while (curr)
	{
		amount += 1;
		curr = (t_env_nodes *)curr->base.next;
	}
	return (allocate_env_arr(data, data->env, amount));
}

static int	allocate_env_arr(t_struct_ptrs *data, t_env_nodes *env, int amount)
{
	char	*tmp;
	int		i;

	data->exec_env = ft_calloc(amount + 1, sizeof(char *));
	if (!data->exec_env)
		return (FAIL);
	i = 0;
	while (env)
	{
		tmp = ft_strdup(env->var_name);
		if (!tmp)
			return (clean_up_arr(&data->exec_env), FAIL);
		data->exec_env[i] = ft_strjoin(tmp, env->var_value);
		free(tmp);
		if (!data->exec_env[i])
			return (clean_up_arr(&data->exec_env), FAIL);
		env = (t_env_nodes *)env->base.next;
		i++;
	}
	data->exec_env[i] = NULL;
	return (SUCCESS);
}

int	split_env_path(t_struct_ptrs *data, t_input *curr)
{
	char	*path_str;

	if (!data->env)
	{
		if (check_if_cmd_is_path(curr) == YES)
			return (SUCCESS);
		return (EMPTY);
	}
	path_str = get_var_value(data->env, "PATH=");
	if (!path_str)
	{
		if (check_if_cmd_is_path(curr) == YES)
			return (SUCCESS);
		return (NOT_FOUND);
	}
	data->split_path = ft_split(path_str, ':');
	if (!data->split_path)
		return (FAIL);
	return (SUCCESS);
}
