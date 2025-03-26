#include "../../inc/execution.h"

void	init_cmd_arr(t_struct_ptrs *data);

//////////////	DEBUGGING THINGS - DELETE
int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_struct_ptrs	data;
	//int	i = 0;
	int	ret_val;

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


	ret_val = cd(&data);
		printf("\n\nExit Code: %d\n\n\n\n", ret_val);


	free(data.input->cmd_arr);
	free(data.input);
	data.input = NULL;

	env(&data);
	printf("\n\nENV printed\n\n");
	export(&data);
	printf("\n\nEXPORT printed\n\n");

	free_env_nodes(&data.env);
	free_env_nodes(&data.export);
	//free(data.input->cmd_arr);
	//free(data.input);
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
	data->input->cmd_arr[0] = "cd";
	data->input->cmd_arr[1] = "/mnt/c/Users/gebog/Desktop/Hive/";
	//data->input->cmd_arr[1] = "G8=";
	//data->input->cmd_arr[2] = "z1";
	//data->input->cmd_arr[3] = "_A1";
	//data->input->cmd_arr[4] = "A7=";
	//data->input->cmd_arr[4] = "T1_2";
	//data->input->cmd_arr[3] = "unset";
	// data->input->cmd_arr[8] = "T5";
	data->input->cmd_arr[2] = NULL;
}
