#ifndef TOKEN_H
# define TOKEN_H

#include "execution.h"

typedef enum e_token_num
{
	WORD,
	INPUT, // >
	OUTPUT, // <
	HEREDOC, // <<
	APPEND, // >>
	REDIR, // everthing including ><>><<
	INFILE, // things after > or >>
	OUTFILE, // things after < or <<
	PIPE, // |
}					t_token_type;

typedef struct s_token
{
	t_list_base		base;
	t_token_type	type;
	char			*value;
}					t_token;


#endif
