#include "../../../inc/execution.h"

int		cd_to_home(t_struct_ptrs *data);
void	cd_error_print(char *path, int err);

int	cd(t_struct_ptrs *data)
{
	char	buff[PATH_MAX];

	if (!data->input->cmd_arr[1])
		return (cd_to_home(data));
	else if (data->input->cmd_arr[1] && !data->input->cmd_arr[2])
	{
		if (chdir(data->input->cmd_arr[1]) == 0)
		{
			if (!getcwd(buff, PATH_MAX))
				return (FAIL);
			update_var_in_both(data->env, data->export, "OLDPWD=", \
								get_var_value(data->env, "PWD="));
			update_var_in_both(data->env, data->export, "PWD=", buff);
			return (SUCCESS);
		}
		else
			return (cd_error_print(data->input->cmd_arr[1], 1), FAIL);
	}
	else
		return (cd_error_print(data->input->cmd_arr[1], 2), FAIL);
}

int	cd_to_home(t_struct_ptrs *data)
{
	char	*home;

	update_var_in_both(data->env, data->export, "OLDPWD=", \
				get_var_value(data->env, "PWD="));
	home = get_var_value(data->env, "HOME=");
	if (!home)
		return (ft_putstr_fd("catshell: cd: HOME not set\n", 2), FAIL); //CHANGE NAME OF SHELL????
	if (!chdir(home))
		return (update_var_in_both(data->env, data->export, "PWD=", home), \
				SUCCESS);
	return (FAIL);
}

void	cd_error_print(char *path, int err)
{
	if (err == 1)
	{
		ft_putstr_fd("catshell: cd: ", 2); // CHANGE NAME OF SHELL????
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	if (err == 2)
		return (ft_putstr_fd("cd: too many arguments\n", 2), (void)0);
}
