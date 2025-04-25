#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "execution.h"
# include "expansion.h"
# include "lexer.h"
# include "parsing.h"
# include "signal.h"
# include "utils.h"

# define PROMPT "\033[1;38;5;218m🐱 --Catshell > \033[0m"
# define FAIL 1
# define SYS_FAIL -1
# define SUCCESS 0
# define YES 1
# define NO 0
# define NOT_FOUND 2
# define EMPTY 3
# define IS_OK_TO_RUN(x) ((x) == SUCCESS || (x) == EMPTY)
# define FT_SPACE " \t\n"
# define FT_DELIMINATER "|;&()<>"
# define HEREDOC_TEMP_NAME ".heredoc_no_"

extern sig_atomic_t	g_signal_numb;

#endif
