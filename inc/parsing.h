#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "structure.h"

t_input	*parser(t_struct_ptrs *data);
int		parse_heredoc(t_struct_ptrs *data);
int		parse_redirection(t_token **token, t_input **input);

// utils
int		cmd_arr_num(t_token *token_list);
void	print_input(t_input *head);
int		check_for_expansion(t_struct_ptrs *data, char **new_line);
char	get_quote_mark(char *src);
void	get_next_cmd_node(t_token **token_list);
char	*generate_heredoc_name(void);
int		get_redir_num(t_token *token, t_token_type redir);
int		is_last_file_append(t_token *token);

#endif
