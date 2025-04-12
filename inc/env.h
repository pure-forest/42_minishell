#ifndef ENV_H
# define ENV_H

# include "minishell.h"
# include "structure.h"

//**************		ENV & EXPORT -- PLUS UTILS
int			create_env(char **envp, t_struct_ptrs *data);
int			create_export(t_struct_ptrs *data);
char		*get_var_value(t_env_nodes *list, char *var);
int			change_var_value(t_env_nodes *list, char *var_to_change,
				char *new_value, int offset);
void		update_var_in_both(t_env_nodes *env, t_env_nodes *export,
				char *var_to_change, char *new_value);
t_env_nodes	*find_position(t_env_nodes *root, t_env_nodes *new_var);
int			update_env(t_struct_ptrs *data);

#endif