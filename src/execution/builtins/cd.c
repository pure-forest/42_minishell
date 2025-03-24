/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:57:43 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/19 19:57:43 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

#define PATH_MAX 100

//DEFINES
//int		cd_to_home(t_struct_ptrs *data);
//int		cd_error_print(char *path);
// char	*get_varlist_value(t_struct_ptrs *data, var);
// void	change_var_value(t_struct_ptrs *data, var_to_change, new_value);
// int		update_pwd(t_struct_ptrs *data);

/*int	cd(char	**cmd_arr)	//t_struct_ptrs *data)
{
	printf("Path: %s\n", cmd_arr[1]);
	//chdir(cmd_arr[1]);
	return (chdir(cmd_arr[1]));
}*/

int	add_to_cmd_arr(t_input *inp, int token_value)
{
	char	*arr;
	char	*tmp;

	arr = ft_calloc(11, sizeof(char *));
}


char	**create_cmd_args(t_struct_ptrs *data)
{
	t_input	*curr;
	int		count;

	curr = NULL;
	if (data->input)
	{
		curr = (t_input *)data->input;
		count = count_tokentype_amount(curr, ARG);
		while(curr)
		{
			if (curr->inp->token_type == ARG)
				if (add_to_cmd_arr(data, data->inp->token_value))
					return (FAIL);
			curr = (t_input *)curr->base.next;
		}
		return (SUCCESS);
	}
	return (FAIL);
}

/*int	cd(t_struct_ptrs *data)
{
	char	*cwd;
	char	buff[PATH_MAX];
	// if (!data->inp->token_value[1])
	// 	return (cd_to_home(data));

	cwd = getcwd(buff, PATH_MAX);
	if (cwd != NULL)
		printf("My current working directory is %s\n", cwd);

	if (chdir(data->inp->token_value[1]) != 0) //this cannot just be directly input, i need to create cmd arr
		//return (cd_error_print(data->inp->token_value[1]));
		return (printf("ERROR\n"), FAIL);
	cwd = getcwd(buff, PATH_MAX);
	if (cwd != NULL)
		return (printf("My new directory is %s\n", cwd), SUCCESS);
	return (FAIL);
	// change_var_value(data, "OLDPWD", get_varlist_value(data, "PWD"));
	// return (update_pwd(data));
}*/

// int	cd_to_home(t_struct_ptrs *data)
// {
// 	char	*home;

// 	change_var_value(data, "OLDPWD", get_varlist_value("PWD"));
// 	home = get_varlist_value("HOME");
// 	if (!home)
// 		return (ft_putstr_fd("catshell: cd: HOME not set\n", 2), FAIL);
// 	if (chdir(home))
// 		return (change_var_value(data, "PWD", home));
// 	return (FAIL);
// }

// int	cd_error_print(char *path)
// {
// }

// int	update_pwd(t_struct_ptrs *data)
// {
// 	//call getcwd because if it was successfull then it is updated and you can get the new value this way

// }

/// THIS I CAN PUT IN A ENV/EXPORT UTILS FILE
// char	*get_varlist_value(t_struct_ptrs *data, var)
// {

// }

// void	change_var_value(t_struct_ptrs *data, var_to_change, new_value)
// {

// }



/*int	main(void)
{
	char	**cmd_arr;
	char	*cwd;
	char	buff[PATH_MAX];
	int		res;

	cmd_arr = malloc(sizeof (char *) *3);
	if (!cmd_arr)
		return (-1);
	cmd_arr[0] = "cd";
	//cmd_arr[1] = "/mnt/c/Users/gebog/Desktop/Hive/MiniShell/42_minishell/src/execution/";
	cmd_arr[1] = "/mnt/c/Users/gebog/Desktop/Hive/MiniShell/";
	//cmd_arr[1] = "../../";
	//cmd_arr[1] = "/home";
	cmd_arr[2] = NULL;
	cwd = getcwd(buff, PATH_MAX);
	if (cwd != NULL)
		printf("My working directory is %s\n", cwd);
	res = cd(cmd_arr);
	printf("Cd res: %d\n", res);
	cwd = getcwd(buff, PATH_MAX);
	if (cwd != NULL)
		printf("My new directory is %s\n", cwd);

	return (0);
}*/
