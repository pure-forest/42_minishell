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
	INPUT, // <
	OUTPUT, // >
	HEREDOC, // <<
	APPEND, // >>
	REDIR, // everthing including ><>><<
	INFILE, // things after > or >>
	OUTFILE, // things after < or <<
	PIPE, // |
}					t_token_type;

//should be freed before execution? Or not
typedef struct s_token
{
	t_list_base		base;
	t_token_type	type;
	int				quote_count;
	bool			should_expand;
	char			*value;
}					t_token;

//The main structure will be used in the execution phase
typedef struct s_input
{
	t_list_base	base;
	char		**cmd_arr;
	char		**redir_in;
	char		**redir_out;
	int			input_fd;
	int			output_fd;
}				t_input;

//main struct for everyting used in minshell
typedef struct s_struct_ptrs
{
	t_env_nodes			*env;
	t_env_nodes			*export;
	t_token				*token;
	t_input				*input;
	int					exit_code;
	char				**exec_env;
}						t_struct_ptrs;

#endif
