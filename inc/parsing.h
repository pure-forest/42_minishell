#ifndef PARSING_H
# define PARSING_H

# include "lexer.h"
# include "minishell.h"
# include "structure.h"

t_input	*parser(t_token *token_list);
t_input	*cmd_table_init(char **cmd_arr);
void	free_cmd_table(t_input **head);
void	print_input(t_input *head);
t_input	*get_input(t_input *cmd_table);

#endif
