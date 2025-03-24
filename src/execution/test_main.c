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

//void	init_cmd_arr(t_struct_ptrs *data);
int	fill_tokens(t_struct_ptrs *data);

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
	//init_cmd_arr(&data);

	//env(&data);
	//export(&data);
    //pwd(&data);
	//unset(&data);
	//printf("\n\n Unset is done\n\n");
	//env(&data);
	
	//printf("\n\n\n  ENV HAS BEEN PRINTED \n\n\n");

	//export(&data);
	//printf("\n\nUnset has been processed\n\n\n");

	if (fill_tokens(&data))
		return (printf("Failure in fill tokens\n"), FAIL);
	else
		print_list((t_list_base *)data.input, print_inp_nodes);

	//cd(&data);

	free_env_nodes(&data.env);
	free_env_nodes(&data.export);
	//free(data.cmd_arr);
	return (0);
}

/*void	init_cmd_arr(t_struct_ptrs *data)
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
}*/

//// EXAMPLE
//	 cd ../

int	fill_tokens(t_struct_ptrs *data)
{
	t_input	*new_token;
	t_input	*new_token_2;
	t_input	*new_token_3;

	new_token = malloc(sizeof(t_input));
	if (!new_token)
		return (FAIL);
	new_token->base.next = NULL;
	new_token->token_type = CMD;
	new_token->token_value = malloc(sizeof(char *) * 2);
	new_token->token_value[0] = "cd";
	//new_token->token_value[1] = "two";
	new_token->token_value[1] = NULL;
	new_token->base.prev = NULL;
	data->input = new_token;
	new_token_2 = malloc(sizeof(t_input));
	if (!new_token_2)
		return (FAIL);
	new_token_2->token_type = ARG;
	new_token_2->token_value = malloc(sizeof(char *) * 2);
	new_token_2->token_value[0] = "../";
	//new_token_2->token_value[1] = "smth";
	new_token_2->token_value[1] = NULL;
	if (append_node((t_list_base *)data->input, (t_list_base *)new_token_2))
			return (FAIL);
	new_token_3 = malloc(sizeof(t_input));
	if (!new_token_3)
		return (FAIL);
	new_token_3->token_type = ARG;
	new_token_3->token_value = malloc(sizeof(char *) * 2);
	new_token_3->token_value[0] = "one";
	new_token_3->token_value[1] = NULL;
	//new_token_3->token_value[2] = "three";
	if (append_node((t_list_base *)data->input, (t_list_base *)new_token_3))
			return (FAIL);
	return (SUCCESS);
}
