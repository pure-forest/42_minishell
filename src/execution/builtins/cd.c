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
int	cd(char	**cmd_arr)	//t_struct_ptrs *data)
{
	printf("Path: %s\n", cmd_arr[1]);
	//chdir(cmd_arr[1]);
	return (chdir(cmd_arr[1]));
}

int	main(void)
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
}