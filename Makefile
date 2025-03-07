NAME=minishell
SRCDIR=src
OBJDIR=obj
BINDIR=bin
CC=cc
FLAGS=-Wall -Wextra -Werror

SRC=${addprefix ${SRCDIR}/, main.c}
OBJ=${SRC:${SRCDIR}%.c=${OBJDIR}/%.o}

PINK = \033[38;5;218m
END = \033[0m

all:$(BINDIR)/${NAME}

${OBJDIR}:
	@mkdir -p obj

$(BINDIR):
	@mkdir -p bin

${OBJDIR}/%.o:${SRCDIR}/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -o $@ -c $<

$(BINDIR)/${NAME}:${OBJ} | $(BINDIR)
	@$(CC) $(OBJ) -o $(BINDIR)/$(NAME) && \
	printf "$(PINK)=== ✅Minishell compile succeed. $(END)\n"

clean:
	@rm -rf $(OBJ) $(OBJDIR) && \
	printf "$(PINK)=== 🚮Minishell clean succeed. $(END)\n"

fclean:clean
	@rm -rf $(NAME) $(BINDIR) && \
	printf "$(PINK)=== 🔁Minishell fclean succeed. $(END)\n"

mac:all clean

re: fclean all

.PHONY: all clean fclean mac re

