/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:39:29 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/22 14:16:07 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "lexer.h"

# define PINK "\033[1;38;5;218m"
# define END "\033[0m"
# define PROMPT PINK "🐱 --Catshell > " END

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

void					cmd_table_init(char *str, t_cmd_table **cmd);
void					print_parser_list(t_cmd_table *parser);
void					free_cmd_table(t_cmd_table **head);
void					trim_and_free(char **src);

#endif
