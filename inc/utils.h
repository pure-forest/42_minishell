#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

//**************		STRING UTILS
int			ft_strcmp(char *s1, char *s2);
char		*ft_strndup(const char *s, size_t len);
char		*ft_strjoin_and_free(char const *s1, char const *s2);
char		*append_character_in_string(char *s1, char c);

//**************		NODE UTILS
int			append_node(t_list_base **list_to_modify, t_list_base *new_var);
t_list_base	*find_last(t_list_base *root);

// clean up funtions
void		free_lexer(t_token **head);
void		ft_free_double_ptr(char **str);
void		free_one_env_node(t_env_nodes *node_to_free);
void		free_env_nodes(t_env_nodes **root);
void		clean_up_arr(t_struct_ptrs *data);
void		free_cmd_table(t_input **head);

// init functions
t_input		*cmd_table_init(char **cmd_arr);
t_token		*token_init(t_token_type type, char *token_value);

// error handling
void		error_handling(t_struct_ptrs *data);

#endif
