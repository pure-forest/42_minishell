/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:39:29 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/17 15:46:09 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

# define PINK "\033[1;38;5;218m"
# define END "\033[0m"
# define PROMPT PINK "🐱 --Catshell > " END

typedef enum e_token_num
{
	WORD,
	OUTPUT,
	INPUT,
	HEREDOC,
	PIPE,
}						t_token_type;

typedef enum e_file_descpritor
{
	STD_IN,
	STD_OUT,
	STD_ERR,
}						t_file_descpritor;

typedef struct s_token
{
	t_token_type		type;
	int					pipe_index;
	char				*value;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_cmd_table
{
	char				**cmd_args;
	int					index;
	char				*cmd;
	char				*input_file;
	char				*output_file;
	t_token				*redirection;
	struct s_cmd_table	*next;
}						t_cmd_table;

typedef struct s_memory_list
{
	char				*value;
	char				*next;
}						t_memory_list;

void					token_init(char *str, t_token **head);
void					print_token_list(t_token *lexer);
void					cmd_table_init(t_token **token, t_cmd_table **cmd);
void					print_parser_list(t_cmd_table *parser);
void					free_lexer(t_token **head);
void					push_to_list(t_token_type num, char *value, int index,
							t_token **head);

#endif
