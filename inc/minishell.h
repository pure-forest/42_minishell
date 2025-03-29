#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/stat.h>
# include <fcntl.h>


# include "../libft/libft.h"
# include "lexer.h"
# include "parsing.h"
# include "execution.h"

# define PINK "\033[1;38;5;218m"
# define BLUE "\033[1;34m"
# define END "\033[0m"
# define PROMPT PINK "🐱 --Catshell > " END
# define FAIL 1
# define SUCCESS 0
# define ERROR -1
# define FT_SPACE " \t\n"
# define FT_DELIMINATER "|;&()\"\'<>"



#endif
