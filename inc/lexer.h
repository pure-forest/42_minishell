#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "parsing.h"

# define ERROR -1
# define FT_SPACE " \t\n"
# define FT_DELIMINATER "|;&()\"\'<>"

typedef enum e_token_num
{
	WORD,
	INPUT,
	OUTPUT,
	HEREDOC,
	REDIR,
	INFILE,
	OUTFILE,
	PIPE,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer
{
	t_token			*list_of_token;
	size_t			size;
}					t_lexer;

void				print_token_list(t_token *lexer);
void				free_lexer(t_token **head);
t_token				*token_init(char *str);
int					tokenize_text(char *str, int *i, t_token **token_list);
int					tokenize_quote(char *str, int *i, t_token **token_list);
int					tokenize_pipe(char *str, int *i, t_token **token_list);
int					tokenize_redir(char *str, int *i, t_token **token_list);
int					check_redir_file(t_token *token_list);
int					check_pipe(t_token *token_list);
int					check_heredoc(t_token *token_list);
t_token				*node_init(t_token_type type, char *token_value);
int					append_node(t_token *node, t_token *head);
int					tokenize_heredoc(t_token **token_list);

#endif
