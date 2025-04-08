#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "../libft/libft.h"
# include "lexer.h"
# include "parsing.h"
# include "execution.h"
# include "expansion.h"

# define PINK "\033[1;38;5;218m"
# define BLUE "\033[1;34m"
# define END "\033[0m"
# define PROMPT PINK "🐱 --Catshell > " END
# define FAIL 1
# define SUCCESS 0
# define YES 1
# define NO 0
# define FT_SPACE " \t\n"
# define FT_DELIMINATER "|;&()<>"



#endif
