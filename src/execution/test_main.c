#include "../../inc/execution.h"

void	init_cmd_arr(t_struct_ptrs *data);
void	init_input(t_struct_ptrs *data);
void	set_redirection(char *input, char *output, t_input *node);

//////////////	DEBUGGING THINGS - DELETE
int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	//envp = NULL;
	t_struct_ptrs	data;

	data = (t_struct_ptrs){0};
	if (create_env(envp, &data))
	 	return (FAIL);
	if (create_export(&data))
		return (FAIL);

	// env(&data);
	// printf("\n\nENV printed\n\n");
	// // export(&data);
	// // printf("\n\nEXPORT printed\n\n");

	init_input(&data);
	printf("\n\nPrinting INPUT\n\n");
	print_list((t_list_base *)data.input, print_inp_nodes);
	// print_cmd_arr(data.input->cmd_arr);

	printf("\n\nProcessing Execute\n");
	execute(&data);
	printf("\n\nExecute Exit Code: %d\n\n\n", data.exit_code);

	// printf("\n\nPRINTING ENV AFTER SETTING:\n");
	// printf("-------------------------------------------------------------\n");
	// env(&data);
	// printf("-------------------------------------------------------------\n");
	// printf("\n\nPRINTING EXPORT AFTER SETTING:\n");
	// printf("------------------------------------------------------------\n");
	// export(&data);
	// printf("------------------------------------------------------------\n");

	error_handling(&data);
	if (data.input)
	{
		t_input *curr = data.input;
		t_input	*next;
		while (curr)
		{
			next = (t_input *)curr->base.next;
			if (curr->cmd_arr)
				free(curr->cmd_arr);
			if (curr->redir_in)
				free(curr->redir_in);
			if (curr->redir_out)
				free(curr->redir_out);
			free(curr);
			curr = next;
		}
	}
	return (0);
}

//	EXAMPLLE:	cd .. one two
// void	init_cmd_arr(t_struct_ptrs *data)
// {
// 	if (!data->input)
// 	{
// 		data->input = malloc(sizeof(t_input));
// 		if (!data->input)
// 			return (printf("Failure with cmd_arr malloc"), (void)0);
// 	}
// 	data->input->cmd_arr = malloc(sizeof(char *) * 6);
// 	if (!data->input->cmd_arr)
// 		return ;
// 	data->input->cmd_arr[0] = "cat";
// 	data->input->cmd_arr[1] = "Makefile";
// 	// data->input->cmd_arr[2] = "A1=test";
// 	// data->input->cmd_arr[3] = "G1=test";
// 	// data->input->cmd_arr[4] = "Z1";
// 	data->input->cmd_arr[2] = NULL;
// }

void	init_input(t_struct_ptrs *data)
{
	// if (!data->input)
	// {
	// 	data->input = malloc(sizeof(t_input));
	// 	if (!data->input)
	// 		return (printf("Failure with cmd_arr malloc"), (void)0);
	// }

	t_input	*new_var;
	new_var = malloc(sizeof(t_input));
	if (!new_var)
		return ;
	*new_var = (t_input){0};
	new_var->cmd_arr = malloc(sizeof(char *) * 3);
	if (!new_var->cmd_arr)
		return ;
	new_var->cmd_arr[0] = "cat";
	new_var->cmd_arr[1] = "inf";
	new_var->cmd_arr[2] = NULL;
	new_var->redir_in = malloc(sizeof(char *) * 4);
	if (!new_var->redir_in)
		return ;
	// new_var->redir_in[0] = "infile";
	// new_var->redir_in[1] = "inf1";
	// new_var->redir_in[0] = "inf";
	new_var->redir_in[0] = NULL;
	new_var->redir_out = malloc(sizeof(char *) * 3);
	if (!new_var->redir_out)
		return ;
	// new_var->redir_out[0] = "out";
	// new_var->redir_out[0] = "outf";
	new_var->redir_out[0] = NULL;
	new_var->base.next = NULL;
	data->input = new_var;

	// t_input *second;
	// second = malloc(sizeof(t_input));
	// if (!second)
	// 	return ;
	// *second = (t_input){0};
	// second->cmd_arr = malloc(sizeof(char *) * 3);
	// if (!second->cmd_arr)
	// 	return ;
	// second->cmd_arr[0] = "grep";
	// second->cmd_arr[1] = "NAME";
	// second->cmd_arr[2] = NULL;
	// second->redir_in = malloc(sizeof(char *) * 4);
	// if (!second->redir_in)
	// 	return ;
	// // second->redir_in[0] = "inf";
	// // second->redir_in[1] = "inf1";
	// // second->redir_in[0] = "Makefile";
	// second->redir_in[0] = NULL;
	// second->redir_out = malloc(sizeof(char *) * 3);
	// if (!second->redir_out)
	// 	return ;
	// // second->redir_out[0] = "out";
	// // second->redir_out[1] = "outf";
	// second->redir_out[0] = NULL;

	// second->base.next = NULL;
	// second->base.prev = (t_list_base *)new_var;
	// new_var->base.next = (t_list_base *)second;

	// t_input	*third;
	// third = malloc(sizeof(t_input));
	// if (!third)
	// 	return ;
	// *third = (t_input){0};
	// third->cmd_arr = malloc(sizeof(char *) * 3);
	// third->cmd_arr[0] = "grep";
	// third->cmd_arr[1] = "rm";
	// third->cmd_arr[2] = NULL;
	// third->redir_in =  malloc(sizeof(char *) * 4);
	// if (!third->redir_in)
	// 	return ;
	// third->redir_in[0] = NULL;
	// third->redir_out = malloc(sizeof(char *) * 3);
	// if (!third->redir_out)
	// 	return ;
	// third->redir_out[0] = NULL;
	// third->base.prev = (t_list_base *)second;
	// third->base.next = NULL;
	// second->base.next = (t_list_base *)third;
}

// void	set_redirection(char *input, char *output, t_input *node)
// {
// 	t_token	*redir_in;
// 	redir_in = malloc(sizeof(t_token));
// 	if (!redir_in)
// 		return ;
// 	*redir_in = (t_token){0};
// 	redir_in->type = INPUT;
// 	redir_in->value = input;
// 	redir_in->base.next = NULL;
// 	node->redirection = redir_in;
// 	t_token	*redir_out;
// 	redir_out = malloc(sizeof(t_token));
// 	if(!redir_out)
// 		return ;
// 	*redir_out = (t_token){0};
// 	redir_out->type = OUTPUT;
// 	redir_out->value = output;
// 	redir_out->base.next = NULL;
// 	redir_out->base.prev = (t_list_base *)redir_in;
// 	redir_in->base.next = (t_list_base *)redir_out;
// }
