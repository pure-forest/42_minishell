#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"
# include "structure.h"

char	*expand_variable(t_struct_ptrs *data, char *src);
int		expand_word_token(t_struct_ptrs *data);

bool	is_valid_expandable(char c);
bool	should_just_append(char c, char *src);
char	*handle_exit_code(t_struct_ptrs *data);
void	strcpy_to_valid_variable(char *src, char **valid_variable, int *i,
			int *j);
char	*handle_non_valid_expansion(char **valid_variable);

#endif
