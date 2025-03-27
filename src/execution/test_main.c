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
	if (!(create_env(envp, &data)))
		return (-1);
  	 if (!(create_export(&data)))
		return (-1);

	init_cmd_arr(&data);
	printf("\n\nPrinting CMD_ARR\n");
	print_cmd_arr(data.input->cmd_arr);

	env(&data);
	//export(&data);
    //pwd(&data);
	//unset(&data);
	//printf("\n\n Unset is done\n\n");
	//env(&data);
	ret_val = cd(&data);
	printf("\n\nExit Code: %d\n\n", ret_val);

	//export(&data);
	env(&data);
	//printf("\n\nUnset has been processed\n\n\n");

	free_env_nodes(&data.env);
	free_env_nodes(&data.export);
	free(data.input->cmd_arr);
	free(data.input);
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

	data->input->cmd_arr = malloc(sizeof(char *) * 3);
	if (!data->input->cmd_arr)
		return ;
	data->input->cmd_arr[0] = "cd";
	//data->input->cmd_arr[1] = NULL;
	data->input->cmd_arr[1] = "~";
	//data->input->cmd_arr[1] = "/home/gboggion/Studies/Minishell/42_minishell";
	// data->input->cmd_arr[2] = "one";
	// data->input->cmd_arr[3] = "two";
	// data->input->cmd_arr[4] = "T1_2";
	// data->input->cmd_arr[5] = "T1_3";
	// data->input->cmd_arr[6] = "T7";
	// data->input->cmd_arr[7] = "unset";
	// data->input->cmd_arr[8] = "T5";
	data->input->cmd_arr[2] = NULL;
}
