/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:30:37 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/29 11:39:10 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_ok_to_run(t_struct_ptrs *data, char **envp);

int	main(int argc, char **av, char **envp)
{
	char			*read_line;
	t_struct_ptrs	*data;

	data = &((t_struct_ptrs){0});
	if (!argc || !av || is_ok_to_run(data, envp) == FAIL)
		return (FAIL);
	set_shell_level(data, NULL);
	while (1)
	{
		signal_init();
		g_signal_numb = 0;
		read_line = readline(PROMPT);
		if (!read_line)
			break ;
		signal_init_interrupt(data);
		add_history(read_line);
		if (start_tokenization(read_line, data) == FAIL)
		{
			free_lexer(&data->token);
			continue ;
		}
		execute(data);
		mini_clean(data);
	}
	return (mega_clean(data), 0);
}

static int	is_ok_to_run(t_struct_ptrs *data, char **envp)
{
	int	return_value;

	return_value = create_env(envp, data);
	if (return_value == FAIL)
		return (FAIL);
	return_value = create_export(data);
	if (return_value == FAIL)
		return (FAIL);
	return (SUCCESS);
}
