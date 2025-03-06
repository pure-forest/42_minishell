NAME=minishell
SRCDIR=src
OBJDIR=obj
CC=cc
FLAGS=-Wall -Wextra -Werror

SRC={$addprefix ${SRCDIR}/, main.c}
OBJ={SRC:${SRCDIR}%.c=${OBJDIR}/%.o}

all:${NAME}

${OBJDIR}:
	mkdir -p obj

${NAME}:${OBJ}
	