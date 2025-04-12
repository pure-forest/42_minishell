#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "structure.h"

//**************		Execution
void	execute(t_struct_ptrs *data);

//**************		Execute Utils
int		is_builtin(t_struct_ptrs *data);
int		launch_builtin(t_struct_ptrs *data);
int		create_execute_env(t_struct_ptrs *data);
int		get_err_code(int err);
int		check_inp_files(t_struct_ptrs *data, t_input *input, char **redir_in,
			int *pipe_fd);
int		check_out_files(t_struct_ptrs *data, t_input *input, char **redir_out,
			int *pipe_fd);
int		set_std_fds(t_struct_ptrs *data, t_input *input, int *pipe_fd,
			int prev_read_end);

//**************		EXEC ERROR HANDLING
// void					print_err_exe(t_input *curr, int err);
// void					print_err_exe(t_struct_ptrs *data, t_input *curr,
						// int err);
void	print_err_exe(t_struct_ptrs *data, char *cmd, int err);
void	close_fd(int *fd);
int		get_errno_codes(int err);
void	set_exit_code(t_struct_ptrs *data, int err);

//**************		BUILTINS
int		env(t_struct_ptrs *data);
int		pwd(t_struct_ptrs *data);
int		export(t_struct_ptrs *data);
int		unset(t_struct_ptrs *data);
int		cd(t_struct_ptrs *data);
int		echo(t_struct_ptrs *data);
int		is_equal_sign_present(char *arg);
int		check_match(char *cmd_arg, char *var_name);
int		remove_node(t_env_nodes **lst_to_unset, t_env_nodes *curr);
void	does_var_exist(t_env_nodes **list, char *arg);

void	free_one_env_node(t_env_nodes *node_to_free);

//**************		ERROR HANDLING
void	error_handling(t_struct_ptrs *data);
void	free_env_nodes(t_env_nodes **root);
void	clean_up_arr(t_struct_ptrs *data);
// void					clean_up_arr(char **env_arr);

//*************			DEBUGGING __ DELETEEEEEEEE!!!!!!!!!!!!!!!!!
void	print_list(t_list_base *head, void (*print_node)(void *));
void	print_env_nodes(void *node);
void	print_inp_nodes(void *node);
void	print_cmd_arr(char **cmd_arr);
int		print_export(t_struct_ptrs *data);

#endif
