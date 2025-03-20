/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:39:29 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/20 17:57:39 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PINK "\033[1;38;5;218m"
# define END "\033[0m"
# define PROMPT PINK "🐱 --Catshell > " END

typedef enum e_token_num
{
	CMD,
	INPUT,
	OUTPUT,
	HEREDOC,
	INFILE,
	OUTFILE,
	PIPE,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_lexer
{
	t_token *list_of_token;
	size_t	size;
}				t_lexer;

typedef struct s_cmd_table
{
	char				**cmd_args;
	int					index;
	char				*cmd;
	char				*input_file;
	char				*output_file;
	int					redirection;
	struct s_cmd_table	*next;
}						t_cmd_table;

typedef struct s_memory_list
{
	char				*value;
	char				*next;
}						t_memory_list;

void					token_init(char *str, t_token **head);
void					print_token_list(t_token *lexer);
void					cmd_table_init(char *str, t_cmd_table **cmd);
void					print_parser_list(t_cmd_table *parser);
void					free_lexer(t_token **head);
void					free_cmd_table(t_cmd_table **head);
void	ft_free_double_ptr(char **str);
void	trim_and_free(char **src);

#endif
