/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:39:29 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/15 17:29:38 by ydeng            ###   ########.fr       */
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
	HEREDOC,
	OUTPUT,
	APPEND,
	INPUT,
	PIPE,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	int					pipe_index;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_cmd_table
{
	char				*cmd;
	int					index;
	char				**cmd_args;
	char				*heredoc_name;
	t_token				*args;
	t_token				*redirection;
	struct s_cmd_table	*next;
}						t_cmd_table;

typedef struct s_memory_list
{
	char				*value;
	char				*next;
}						t_memory_list;

void					token_input(char *str, t_token **head);
void					print_list(t_token *lexer);

#endif
