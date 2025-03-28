#include "../../inc/execution.h"

int	is_builtin(t_struct_ptrs *data);
int	launch_builtiin(t_struct_ptrs *data);

void	execute(t_struct_ptrs *data)
{
	if (!is_builtin(data))
	{
		data->exit_code = launch_builtiin(data);
		return ;
	}
}

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

int	launch_builtiin(t_struct_ptrs *data)
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
	/*if (ft_strcmp(cmd, "cd"))
		return (cd(data));*/
	return (FAIL);
}
