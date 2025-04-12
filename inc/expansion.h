#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

char	*expand_variable(t_struct_ptrs *data, char *src);
int		expand_word_token(t_struct_ptrs *data);
bool	is_valid_expandable(char c);
bool	should_just_append(char c, char *src);

#endif
