#include "../../inc/execution.h"

//void	init_cmd_arr(t_struct_ptrs *data);
void	init_input(t_struct_ptrs *data);
//void	init_input_2(t_struct_ptrs *data);
//void	set_redirection(char *input, char *output, t_input *node);
// void	set_redirection(t_input *node);
void	set_redirection(t_input *node, int t_one, char *one, int t_two, \
	char *two, int t_three, char *three);

// ccc *.c ../../libft/*.c builtins/*.c -g -o exec
//////////////	DEBUGGING THINGS - DELETE
int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	// envp = NULL;
	t_struct_ptrs	data;

	data = (t_struct_ptrs){0};
	if (create_env(envp, &data))
	 	return (FAIL);
	if (create_export(&data))
		return (FAIL);

	init_input(&data);
	printf("\n\nPrinting INPUT\n\n");
	print_list((t_list_base *)data.input, print_inp_nodes);

	printf("\n\nProcessing Execute\n\n");
	execute(&data);
	printf("\n\n\nFinished execution\nExecute Exit Code is: %d\n\n", data.exit_code);

/*if (data.input)
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

	init_input_2(&data);
	printf("\n\nPrinting INPUT TWO\n\n");
	print_list((t_list_base *)data.input, print_inp_nodes);

	printf("\n\nProcessing Execute TWO\n\n");
	execute(&data);
	printf("\n\n\nFinished execution\nExecute Exit Code is: %d\n\n", data.exit_code);
*/
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
/*			if (curr->redirection)
			{
				t_redir	red_curr = curr->redirection;
				t_redir	*tmp;
				while (red_curr)
				{
					tmp = (t_redir	*)curr->base.next;
					free (red_curr);
					red_curr = tmp;
				}
				free(red_curr);
			}*/
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
	new_var->cmd_arr[0] = "ls";
	// new_var->cmd_arr[1] = "hi";
	new_var->cmd_arr[1] = NULL;
	set_redirection(new_var, APPEND, "out_1", 0, NULL, 0, NULL);
	/*new_var->redir_in = malloc(sizeof(char *) * 4);
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
	new_var->redir_out[0] = NULL;*/
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
	// second->cmd_arr[0] = "echo";
	// second->cmd_arr[1] = "bye";
	// second->cmd_arr[2] = NULL;
	// set_redirection(second, 0, NULL, 0, NULL, 0, NULL);
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
	// third->cmd_arr[1] = "second";
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

 void	set_redirection(t_input *node, int t_one, char *one, int t_two, \
	char *two, int t_three, char *three)
 {
 	t_redir	*redir_1;
 	redir_1 = malloc(sizeof(t_redir));
 	if (!redir_1)
 		return ;
 	*redir_1 = (t_redir){0};
 	redir_1->type = t_one;
 	redir_1->file_name = one;
 	redir_1->base.next = NULL;
 	node->redirection = redir_1;

 	t_redir	*redir_2;
 	redir_2 = malloc(sizeof(t_redir));
 	if (!redir_2)
 		return ;
 	*redir_2 = (t_redir){0};
 	redir_2->type = t_two;
 	redir_2->file_name = two;
	redir_2->base.prev = (t_list_base *)redir_1;
 	redir_2->base.next = NULL;
	redir_1->base.next = (t_list_base *)redir_2;

	t_redir	*redir_3;
	redir_3 = malloc(sizeof(t_redir));
	if (!redir_3)
		return ;
	*redir_3 = (t_redir){0};
	redir_3->type = t_three;
	redir_3->file_name = three;
   	redir_3->base.prev = (t_list_base *)redir_2;
	redir_3->base.next = NULL;
   	redir_2->base.next = (t_list_base *)redir_3;
 }


/*void	init_input_2(t_struct_ptrs *data)
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
}*/
