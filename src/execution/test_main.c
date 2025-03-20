/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:51:25 by gboggion          #+#    #+#             */
/*   Updated: 2025/03/16 18:51:25 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

void	init_cmd_arr(t_struct_ptrs *data);

//////////////	DEBUGGING THINGS - DELETE
int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_struct_ptrs	data;
	//int	i = 0;

	data = (t_struct_ptrs){0};
	if (!(create_env(envp, &data)))
		return (-1);
   if (!(create_export(&data)))
		return (-1);
	init_cmd_arr(&data);
		
	env(&data);
	//export(&data);
    //pwd(&data);
	unset(&data);
	printf("\n\nUnset has been processed\n\n\n");
	env(&data);
	//export(&data);

	free_env_nodes(&data.env);
	free_env_nodes(&data.export);
	free(data.cmd_arr);
	return (0);
}

void	init_cmd_arr(t_struct_ptrs *data)
{
	data->cmd_arr = malloc(sizeof(char *) * 10);
	if (!data->cmd_arr)
		return ;
	data->cmd_arr[0] = "unset";
	data->cmd_arr[1] = "T1";
	data->cmd_arr[2] = "B1";
	data->cmd_arr[3] = "_T1";
	data->cmd_arr[4] = "T1_2";
	data->cmd_arr[5] = "T1_3";
	data->cmd_arr[6] = "T7";
	data->cmd_arr[7] = "unset";
	data->cmd_arr[8] = "T5";
	data->cmd_arr[9] = NULL;
}
