/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboggion <gboggion@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:27:25 by gboggion          #+#    #+#             */
/*   Updated: 2025/04/26 17:27:25 by gboggion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../src/libft/libft.h"
# include "execution.h"
# include "expansion.h"
# include "lexer.h"
# include "parsing.h"
# include "signal.h"
# include "utils.h"

# define PROMPT "\033[1;38;5;218m🐱 --Catshell > \033[0m"
# define SYS_FAIL -1
# define SUCCESS 0
# define FAIL 1
# define YES 1
# define NO 0
# define NOT_FOUND 2
# define EMPTY 3
# define FT_SPACE " \t\n"
# define FT_DELIMINATER "|;&()<>"
# define HEREDOC_TEMP_NAME ".heredoc_no_"

extern sig_atomic_t	g_signal_numb;

#endif
