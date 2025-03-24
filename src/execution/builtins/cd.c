/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/03/19 19:57:43 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/19 19:57:43 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

#define PATH_MAX 100


// DEFINES
int		cd_to_home(t_struct_ptrs *data);
void	cd_error_print(char *path, int err);
char	*get_var_value(t_env_nodes *list, char *var);								//Should go in utils
int		change_var_value(t_env_nodes *list, char *var_to_change, char *new_value);		//Should go in utils

int	cd(t_struct_ptrs *data)
{
	char buff[PATH_MAX];

	if (!data->input->cmd_arr[1] || (!ft_strcmp(data->input->cmd_arr[1], "~"))) //~ is this absoute or relative path?
		return (cd_to_home(data));
	else if (data->input->cmd_arr[1] && !data->input->cmd_arr[2])
	{
		if (chdir(data->input->cmd_arr[1]) == 0)
		{
			change_var_value(data->env, "OLDPWD=", get_var_value(data->env, "PWD="));
			change_var_value(data->env, "PWD=", getcwd(buff, PATH_MAX));
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
	char *home;

	change_var_value(data->env, "OLDPWD=", get_var_value(data->env, "PWD="));
	home = get_var_value(data->env, "HOME=");
	if (!home)
		return (ft_putstr_fd("catshell: cd: HOME not set\n", 2), FAIL);		//CHANGE NAME OF SHELL????
	if (!chdir(home))
		return (change_var_value(data->env, "PWD=", home));
	return (FAIL);
}

void	cd_error_print(char *path, int err)
{
	if (err == 1)
	{
		ft_putstr_fd("catshell: cd: ", 2);									//CHANGE NAME OF SHELL????
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	if (err == 2)
		return (ft_putstr_fd("cd: too many arguments\n", 2), (void)0);
}

/// THIS I CAN PUT IN A ENV/EXPORT UTILS FILE
char	*get_var_value(t_env_nodes *list, char *var)
{
	t_env_nodes *curr;

	curr = list;
	if (curr)
	{
		while (curr)
		{
			if (!ft_strcmp(var, curr->var_name))
				return (curr->var_value);
			curr = (t_env_nodes *)curr->base.next;
		}
	}
	return (NULL);
}

int	change_var_value(t_env_nodes *list, char *var_to_change, char *new_value)  // does this have to be an int? will i need to check if a var got changed/found in future?
{
	t_env_nodes *curr;

	curr = list;
	if (curr)
	{
		while (curr)
		{
			if (!ft_strcmp(var_to_change, curr->var_name))
			{
				free (curr->var_value);
				curr->var_value = NULL;
				if (!(curr->var_value = ft_strdup(new_value)))
					return (FAIL);
			}
			curr = (t_env_nodes *)curr->base.next;
		}
	}
	return (FAIL);
}
