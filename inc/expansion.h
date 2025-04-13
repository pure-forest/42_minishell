#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

//bool to check if should just append or not
bool	is_valid_expandable(char c);
bool	should_just_append(char c, char *src);

//helper
char	*expand_variable(t_struct_ptrs *data, char *src);
int		expand_word_token(t_struct_ptrs *data);
char	*handle_exit_code(t_struct_ptrs *data);

#endif
