#ifndef PARSING_H
# define PARSING_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#define PINK "\033[1;38;5;218m"
#define END  "\033[0m"
#define PROMPT PINK"🐱 --Catshell > "END

void	token_input(char *str);



#endif
