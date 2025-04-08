#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "structure.h"

// main lexer functions
t_token	*lexer(char *str);
int		tokenize_text(char *str, int *i, t_token **token_list);
int		tokenize_quote(char *str, int *i, t_token **token_list);
int		tokenize_pipe(char *str, int *i, t_token **token_list);
int		tokenize_redir(char *str, int *i, t_token **token_list);
int		check_redir_file(t_token *token_list);
int		check_pipe(t_token *token_list);
int		check_heredoc(t_token *token_list);
int		remove_quotes(t_token *token_list, t_struct_ptrs *data);

// helper functions
int		get_character_number(char *src, char not_to_count);
t_token	*get_quote_token(t_token *token_list);
void	free_lexer(t_token **head);
void	ft_free_double_ptr(char **str);

// node functions
t_token	*token_init(t_token_type type, char *token_value);

// delete later
void	print_token_list(t_token *lexer);
void	print_double_ptr(char **str);

#endif
