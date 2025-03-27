#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "execution.h"
# include "token.h"

# define ERROR -1
# define FT_SPACE " \t\n"
# define FT_DELIMINATER "|;&()\"\'<>"


//main lexer functions
t_token				*lexer(char *str);
int					tokenize_text(char *str, int *i, t_token **token_list);
int					tokenize_quote(char *str, int *i, t_token **token_list);
int					tokenize_pipe(char *str, int *i, t_token **token_list);
int					tokenize_redir(char *str, int *i, t_token **token_list);
int					check_redir_file(t_token *token_list);
int					check_pipe(t_token *token_list);

//helper functions
void				free_lexer(t_token **head);
void				print_token_list(t_token *lexer);

//not sure if we need to do this in lexer????
t_token				*token_init(t_token_type type, char *token_value);


void				print_double_ptr(char **str);
void				ft_free_double_ptr(char **str);


#endif
