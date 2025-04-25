#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

char	*append_character_in_string(char *s1, char c);
void	free_lexer(t_token **head);
void	ft_free_double_ptr(char **str);
void	free_cmd_table(t_input **head);
void	free_redir(t_redir **head);
void	mega_clean(t_struct_ptrs *data);
void	mini_clean(t_struct_ptrs *data);
t_input	*cmd_table_init(char **cmd_arr);
t_token	*token_init(t_token_type type, char *token_value);
t_redir	*redirection_init(t_token_type type, char *file_name);
void	free_and_null(char **str);

#endif
