#ifndef PARSING_H
# define PARSING_H

# include "lexer.h"
# include "minishell.h"
# include "structure.h"

# define HEREDOC_TEMP_NAME "tmp/.heredoc_no_"

t_input	*parser(t_struct_ptrs *data);
t_input	*cmd_table_init(char **cmd_arr);
int		cmd_arr_num(t_token *token_list);
void	free_cmd_table(t_input **head);
void	print_input(t_input *head);
char	*free_and_join(char *s1, char *s2);
int		parse_heredoc(t_struct_ptrs *data);
int		check_for_expansion(t_struct_ptrs *data, char **new_line);

#endif
