NAME=minishell
SRCDIR=src
OBJDIR=obj

SRC={$addprefix ${SRCDIR}/, main.c}
OBJ={SRC:${SRCDIR}%.c=${OBJDIR}/%.o}

all:${NAME}

${OBJDIR}:
	mkdir -p obj