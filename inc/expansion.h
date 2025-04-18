#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

bool	is_valid_expandable(char c);
bool	should_just_append(char c, char *src);
char	*expand_variable(t_struct_ptrs *data, char *src);
int		expand_word_token(t_struct_ptrs *data);
char	*handle_exit_code(t_struct_ptrs *data);
void	strcpy_to_valid_variable(char *src, char **valid_variable,
		int *i, int *j);

#endif
