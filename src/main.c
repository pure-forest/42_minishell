/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:42:46 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/27 15:10:03 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char		*read_line;
	t_token		*token;
	t_cmd_table	*cmd_table;

	token = NULL;
	// cmd_table = NULL;
	while (1)
	{
		read_line = readline(PROMPT);
		if (read_line && *read_line)
			add_history(read_line);
		token = lexer(read_line);
		free(read_line);
		if (token)
			print_token_list(token);
		cmd_table = parser(token);
		free_lexer(&token);
		// free_cmd_table(&cmd_table);
	}
	return (0);
}
