/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:42:46 by ydeng             #+#    #+#             */
/*   Updated: 2025/03/14 17:31:09 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*read_line;
	t_token	*token;

	token = NULL;
	while (1)
	{
		read_line = readline(PROMPT);
		if (read_line && *read_line)
			add_history(read_line);
		token_input(read_line, &token);
		print_list(token);
	}
	return (0);
}
