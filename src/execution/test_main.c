#include "../../inc/execution.h"

void	init_cmd_arr(t_struct_ptrs *data);
void	init_cmd_arr_2(t_struct_ptrs *data);

//////////////	DEBUGGING THINGS - DELETE
int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	//envp = NULL;
	t_struct_ptrs	data;
	//int	i = 0;
	//int	ret_val;

	data = (t_struct_ptrs){0};
	if (create_env(envp, &data))
	 	return (FAIL);
	if (create_export(&data))
		return (FAIL);

	env(&data);
	printf("\n\nENV printed\n\n");
	export(&data);
	printf("\n\nEXPORT printed\n\n");

	init_cmd_arr(&data);
	printf("\n\nPrinting CMD_ARR\n\n");
	print_cmd_arr(data.input->cmd_arr);

	printf("\n\nProcessing Execute export T1 T2= G1=test:\n");
	execute(&data);
	printf("\n\nExecute Exit Code: %d\n\n\n", data.exit_code);


	free(data.input->cmd_arr);
	free(data.input);
	data.input = NULL;

	printf("\n\nPRINTING ENV AFTER SETTING:\n");
	printf("-------------------------------------------------------------\n");
	env(&data);
	printf("-------------------------------------------------------------\n");
	printf("\n\nPRINTING EXPORT AFTER SETTING:\n");
	printf("------------------------------------------------------------\n");
	export(&data);
	printf("------------------------------------------------------------\n");

	// init_cmd_arr_2(&data);
	// printf("\n\nPrinting CMD_ARR_TWO\n\n");
	// print_cmd_arr(data.input->cmd_arr);

	// printf("\n\nProcessing Execute UNSET\n");
	// execute(&data);
	// printf("\n\nExecute Exit Code: %d\n\n\n", data.exit_code);

	// free(data.input->cmd_arr);
	// free(data.input);
	// data.input = NULL;
	// printf("\n\nPRINTING ENV:\n\n");
	// env(&data);
	// printf("\n\nPRINTING EXPORT:\n\n");
	// export(&data);

	free_env_nodes(&data.env);
	free_env_nodes(&data.export);
	if (data.input && data.input->cmd_arr)
	{
		free(data.input->cmd_arr);
		free(data.input);
	}
	return (0);
}

//	EXAMPLLE:	cd .. one two

void	init_cmd_arr(t_struct_ptrs *data)
{
	if (!data->input)
	{
		data->input = malloc(sizeof(t_input));
		if (!data->input)
			return (printf("Failure with cmd_arr malloc"), (void)0);
	}

	data->input->cmd_arr = malloc(sizeof(char *) * 6);
	if (!data->input->cmd_arr)
		return ;
	data->input->cmd_arr[0] = "export";
	data->input->cmd_arr[1] = "A1";
	data->input->cmd_arr[2] = "A1=test";
	// data->input->cmd_arr[3] = "G1=test";
	// data->input->cmd_arr[4] = "Z1";
	data->input->cmd_arr[3] = NULL;
}

// void	init_cmd_arr_2(t_struct_ptrs *data)
// {
// 	if (!data->input)
// 	{
// 		data->input = malloc(sizeof(t_input));
// 		if (!data->input)
// 			return (printf("Failure with cmd_arr malloc"), (void)0);
// 	}

// 	data->input->cmd_arr = malloc(sizeof(char *) * 5);
// 	if (!data->input->cmd_arr)
// 		return ;
// 	data->input->cmd_arr[0] = "unset";
// 	data->input->cmd_arr[1] = "A1=";
// 	data->input->cmd_arr[2] = "G1";
// 	data->input->cmd_arr[3] = "T2";
// 	data->input->cmd_arr[4] = NULL;
// }
