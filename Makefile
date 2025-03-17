NAME=minishell
SRCDIR=src
OBJDIR=obj
BINDIR=bin
INCDIR=inc
CC=cc
FLAGS=-Wall -Wextra -Werror -g
PINK = \033[38;5;218m
END = \033[0m

LIBFT_DIR = ./libft
LIBFT_A = ${LIBFT_DIR}/libft.a

PARSE_DIR=${SRCDIR}/parsing
PARSE_INC=${INCDIR}/parsing.h
PARSE_SRC=${addprefix ${PARSE_DIR}/, lexer.c parser.c lexer_utils.c struct_helper.c}
PARSE_OBJ=${PARSE_SRC:${PARSE_DIR}%.c=${OBJDIR}/parsing/%.o}

EXECUTE_DIR=${SRCDIR}/execution
EXECUTE_INC=${INCDIR}/execution.h
EXECUTE_SRC=${addprefix ${EXECUTE_DIR}/, }
EXECUTE_OBJ=${EXECUTE_SRC:${EXECUTE_DIR}%.c=${OBJDIR}/execution/%.o}

SRC=${addprefix ${SRCDIR}/, main.c}
OBJ=${SRC:${SRCDIR}%.c=${OBJDIR}/%.o}


all:$(LIBFT_A) $(BINDIR)/${NAME}

${LIBFT_A}:
	@make -C ${LIBFT_DIR} > /dev/null
	@echo "$(PINK)=== ✅Libft compile succeed.  $(END)\n"

${OBJDIR}:
	@mkdir -p obj

$(BINDIR):
	@mkdir -p bin

${OBJDIR}/%.o:${SRCDIR}/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -o $@ -c $<

${OBJDIR}/parsing/%.o:${PARSE_DIR}/%.c ${PARSE_INC}
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -o $@ -c $<

${OBJDIR}/execution/%.o:${EXECUTE_DIR}/%.c ${EXECUTE_INC}
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -o $@ -c $<

$(BINDIR)/${NAME}:$(LIBFT_A) ${PARSE_OBJ} ${EXECUTE_OBJ} ${OBJ} | $(BINDIR)
	@$(CC) $(PARSE_OBJ) ${EXECUTE_OBJ} $(OBJ) $(LIBFT_A) -lreadline -o $(BINDIR)/$(NAME)
	@echo "$(PINK)=== ✅Minishell compile succeed. $(END)\n"

clean:
	@rm -rf $(OBJ) $(OBJDIR)
	@make clean -C ${LIBFT_DIR} > /dev/null
	@echo "$(PINK)=== 🚮Minishell clean succeed. $(END)\n"

fclean:clean
	@rm -rf $(NAME) $(BINDIR)
	@make fclean -C ${LIBFT_DIR} > /dev/null
	@echo "$(PINK)=== 🔁Minishell fclean succeed. $(END)\n"

mac:all clean

re: fclean all

.PHONY: all clean fclean mac re
