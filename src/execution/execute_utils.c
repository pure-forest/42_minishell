#include "../../inc/execution.h"
#include <errno.h>

int	allocate_env_arr(t_struct_ptrs *data, t_env_nodes *env, int amount);

int	is_builtin(t_struct_ptrs *data)
{
	if(!ft_strcmp(data->input->cmd_arr[0], "cd") \
		|| !ft_strcmp(data->input->cmd_arr[0], "echo") \
		|| !ft_strcmp(data->input->cmd_arr[0], "env") \
		|| !ft_strcmp(data->input->cmd_arr[0], "export") \
		|| !ft_strcmp(data->input->cmd_arr[0], "pwd") \
		|| !ft_strcmp(data->input->cmd_arr[0], "unset"))
		//|| ft_strcmp(data->input->cmd_arr[0], "exit")
		return (SUCCESS);
	else
		return (FAIL);
}

int	launch_builtin(t_struct_ptrs *data)
{
	char	*cmd;

	cmd = data->input->cmd_arr[0];
	if (!ft_strcmp(cmd, "cd"))
		return (cd(data));
	if (!ft_strcmp(cmd, "echo"))
		return (echo(data));
	if (!ft_strcmp(cmd, "env"))
		return (env(data));
	if (!ft_strcmp(cmd, "export"))
		return (export(data));
	if (!ft_strcmp(cmd, "pwd"))
		return (pwd(data));
	if (!ft_strcmp(cmd, "unset"))
		return (unset(data));
	/*if (ft_strcmp(cmd, "exit"))
		return (exit(data));*/
	return (FAIL);
}

int	create_execute_env(t_struct_ptrs *data)
{
	t_env_nodes	*curr;
	int			amount;

	if (!data->env)
		return (FAIL);
	curr = data->env;
	amount = 0;
	while (curr)
	{
		amount += 1; //expected 22
		curr = (t_env_nodes *)curr->base.next;
	}
	return (allocate_env_arr(data, data->env, amount));
}

int	allocate_env_arr(t_struct_ptrs *data, t_env_nodes *env, int amount) //static??
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
			return (clean_up_arr(data), FAIL);
		data->exec_env[i] = ft_strjoin(tmp, env->var_value);
		free (tmp);
		if (!data->exec_env[i])
			return (clean_up_arr(data), FAIL);
		env = (t_env_nodes *)env->base.next;
		i++;
	}
	data->exec_env[i] = NULL;
	return (SUCCESS);
}

int	get_err_code(int err)
{
	if (err == EACCES)
		return (126);
	if (err == ENOENT)
		return (127);
	return (1);
}