/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:39:29 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/24 15:39:10 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "lexer.h"

typedef struct s_cmd_table
{
	char				*cmd;
	char				**cmd_args; //need to pass it to the execv() function
	int					index;
	char				*input_file;
	char				*output_file;
	int					redirection;
	bool				have_pipe;
	struct s_cmd_table	*next;
}						t_cmd_table;

void					cmd_table_init(char *str, t_cmd_table **cmd);
void					print_parser_list(t_cmd_table *parser);
void					free_cmd_table(t_cmd_table **head);
void					trim_and_free(char **src);

#endif
