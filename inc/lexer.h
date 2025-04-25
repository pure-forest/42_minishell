#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "structure.h"

int		start_tokenization(char *read_line, t_struct_ptrs *data);
int		tokenize_text(char *str, int *i, t_token **token_list);
int		tokenize_quote(char *str, int *i, t_token **token_list);
int		tokenize_pipe(char *str, int *i, t_token **token_list);
int		tokenize_redir(char *str, int *i, t_token **token_list);
int		check_redir_file(t_token *token_list);
int		check_pipe(t_token *token_list, t_struct_ptrs *data);
int		check_heredoc(t_token *token_list);
int		remove_quotes(t_struct_ptrs *data);
char	*check_quote_expansion(t_struct_ptrs *data, t_token **node, int *i,
			int *j);
bool	should_expand(char c, char quote_mark);
int		get_character_number(char *src, char not_to_count);
t_token	*get_quote_token(t_token *token_list);
bool	should_expand_node(t_token **node, int *i);
char	get_quote_mark(char c);

#endif
