#ifndef STRUCTURE_H
# define STRUCTURE_H

# include "minishell.h"

typedef struct s_list_base
{
	struct s_list_base	*next;
	struct s_list_base	*prev;
}						t_list_base;

typedef struct s_env_nodes
{
	t_list_base			base;
	char				*var_name;
	char				*var_value;
	int					copied;
}						t_env_nodes;

typedef enum e_token_num
{
	WORD,
	QUOTE,
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

typedef struct s_input
{
	t_list_base	base;
	char		*cmd;
	char		**cmd_arr;
	t_token		*args;
	int			index;
	char		*heredoc_name;
	t_token		*redirection;
}				t_input;

typedef struct s_struct_ptrs
{
	t_env_nodes			*env;
	t_env_nodes			*export;
	t_input				*input;
}						t_struct_ptrs;


#endif
