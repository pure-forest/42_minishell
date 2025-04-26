/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:18:19 by ydeng             #+#    #+#             */
/*   Updated: 2025/04/26 17:18:20 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "structure.h"

t_input	*parser(t_struct_ptrs *data);
int		parse_heredoc(t_struct_ptrs *data);
int		parse_redirection(t_token **token, t_input **input);
int		check_for_expansion(t_struct_ptrs *data, char **new_line);
char	*generate_heredoc_name(void);
void	write_into_temp_file(t_token *token, t_struct_ptrs *data, int fd,
			char **temp);
int		cmd_arr_num(t_token *token_list);
void	get_next_cmd_node(t_token **token_list);
int		get_redir_num(t_token *token);

#endif
