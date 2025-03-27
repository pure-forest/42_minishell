#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "lexer.h"

typedef struct s_cmd_table
{
	char				*cmd; //the first WORD token in the list & the first WORD token after pipe
	t_token				*args; // all the other WORD token after *cmd before pipe
	char				**cmd_args; //need to pass it to the execv() function, including *cmd
	int					index;
	char				*heredoc_name; //a string????
	t_token				*redirection; // points to the redirection token???
	struct s_cmd_table	*next;
}						t_cmd_table;


#endif
