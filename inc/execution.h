#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "structure.h"

//**************		Execution
void		execute(t_struct_ptrs *data);

//**************		Execute Utils
int			is_builtin(t_input *curr);
void		launch_builtin(t_struct_ptrs *data, t_input *curr);
int			create_execute_env(t_struct_ptrs *data);
int			get_err_code(int err);
int			check_inp_files(t_struct_ptrs *data, t_input *input,
				char **redir_in, int *pipe_fd);
int			check_out_files(t_struct_ptrs *data, t_input *input,
				char **redir_out, int *pipe_fd);
int			set_std_fds(t_struct_ptrs *data, t_input *input,
				t_exec_data *exec_data);
int			split_env_path(t_struct_ptrs *data);
void		handle_standard_fds(t_exec_data *exec_data, int reset);
void		check_if_cmd_is_path(t_input *curr);
void		make_cmd_path(t_struct_ptrs *data, t_input *curr);
void		turn_cmd_into_directory(t_struct_ptrs *data, t_input *curr, int i,
				char **tmp_cmd_path);
void		wait_for_children(t_struct_ptrs *data);

//**************		EXEC ERROR HANDLING
void		print_err_exe(t_struct_ptrs *data, char *cmd, int err);
void		close_fd(int *fd);
int			get_errno_codes(int err);
void		set_exit_code(t_struct_ptrs *data, int err);

//**************		ENV & EXPORT -- PLUS UTILS
int			create_env(char **envp, t_struct_ptrs *data);
int			create_export(t_struct_ptrs *data);
char		*get_var_value(t_env_nodes *list, char *var);
int			change_var_value(t_env_nodes *list, char *var_to_change,
				char *new_value, int offset);
void		update_var_in_both(t_env_nodes *env, t_env_nodes *export,
				char *var_to_change, char *new_value);
t_env_nodes	*find_position(t_env_nodes *root, t_env_nodes *new_var);
int			update_env(t_struct_ptrs *data, t_input *curr);
int			check_export_syntax(char *arg);
void		set_shell_level(t_struct_ptrs *data);

//**************		BUILTINS
int			env(t_struct_ptrs *data);
int			pwd(t_struct_ptrs *data);
int			export(t_struct_ptrs *data, t_input *curr);
int			unset(t_struct_ptrs *data, t_input *curr);
int			cd(t_struct_ptrs *data, t_input *curr);
int			echo(t_input *curr);
int			ft_exit(t_struct_ptrs *data, t_input *curr);
int			is_equal_sign_present(char *arg);
int			check_match(char *cmd_arg, char *var_name);
int			remove_node(t_env_nodes **lst_to_unset, t_env_nodes *curr);
void		does_var_exist(t_env_nodes **list, char *arg);

//**************		NODE UTILS
int			append_node(t_list_base **list_to_modify, t_list_base *new_var);
t_list_base	*find_last(t_list_base *root);
void	free_one_env_node(t_env_nodes *node_to_free);

//**************		STRING UTILS
int			ft_strcmp(char *s1, char *s2);
char		*ft_strndup(const char *s, size_t len);
char		*ft_strjoin_and_free(char const *s1, char const *s2);
long		ft_atol(const char *s);
int			is_valid_numeric_input(char *arg);

//**************		ERROR HANDLING
void		error_handling(t_struct_ptrs *data);
void		free_env_nodes(t_env_nodes **root);
void		clean_up_arr(char **arr);
void		clean_up_exec_creations(t_struct_ptrs *data, t_input *curr);
void		print_error(char *var, char *var_2, char *str);

//*************			DEBUGGING __ DELETEEEEEEEE!!!!!!!!!!!!!!!!!
void		print_list(t_list_base *head, void (*print_node)(void *));
void		print_env_nodes(void *node);
void		print_inp_nodes(void *node);
void		print_cmd_arr(char **cmd_arr);
int			print_export(t_struct_ptrs *data);

#endif
