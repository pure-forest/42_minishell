NAME=minishell
SRCDIR=src
OBJDIR=obj
BINDIR=bin
INCDIR=inc
TMPDIR=tmp
CC=cc
FLAGS=-Wall -Wextra -Werror -g
SANITIZER=-fsanitize=address -fno-omit-frame-pointer
PINK = \033[38;5;218m
END = \033[0m

LIBFT_DIR = ./libft
LIBFT_A = ${LIBFT_DIR}/libft.a

LEXER=lexer.c lexer_utils.c lexer_reprocess_token.c \
		remove_quotes.c remove_quotes_utils.c lexer_dev.c
PARSER= parser.c parser_utils.c parse_heredoc.c heredoc_utils.c \
		parser_redirection.c parser_dev.c
BUILTIN=cd.c echo.c export_utils.c export.c pwd.c unset.c env.c \
		unset_utils.c exit.c
EXECUTE= error_handling.c exec_utils.c exec_utils_2.c exec_utils_3.c \
	execute_errors.c execute.c  node_utils.c string_utils.c
ENV=create_env.c create_export.c env_export_utils.c
EXPANSION= expansion.c expansion_utils.c
UTILS=clean_up_utils.c init_utils.c string_utils_yutong.c \
		free_functions.c
SIGNAL=signal_init.c signal_utils.c
MINISHEL=main.c

SRC=$(addprefix ${SRCDIR}/, $(MINISHEL)) \
	$(addprefix ${SRCDIR}/lexer/, $(LEXER)) \
	$(addprefix $(SRCDIR)/parser/, $(PARSER)) \
	$(addprefix $(SRCDIR)/execution/, $(EXECUTE)) \
	$(addprefix $(SRCDIR)/execution/builtins/, $(BUILTIN)) \
	$(addprefix $(SRCDIR)/expansion/, $(EXPANSION)) \
	$(addprefix $(SRCDIR)/utils/, $(UTILS)) \
	$(addprefix $(SRCDIR)/execution/, $(ENV)) \
	$(addprefix $(SRCDIR)/signal/, $(SIGNAL))

OBJ=${SRC:${SRCDIR}%.c=${OBJDIR}/%.o}

all:$(LIBFT_A) ${NAME}

${LIBFT_A}:
	@make -C ${LIBFT_DIR} > /dev/null
	@echo "$(PINK)=== ✅Libft compile succeed.  $(END)\n"

${OBJDIR}:
	@mkdir -p obj

$(BINDIR):
	@mkdir -p bin

$(TMPDIR):
	@mkdir -p tmp

${OBJDIR}/%.o:${SRCDIR}/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -o $@ -c $<

${NAME}:$(LIBFT_A) ${OBJ} | $(TMPDIR)
	@$(CC) $(OBJ) $(LIBFT_A) -lreadline  \
	-o $(NAME)
	@echo "$(PINK)=== ✅Minishell compile succeed. $(END)\n"

clean:
	@rm -rf $(OBJ) $(OBJDIR)
	@make clean -C ${LIBFT_DIR} > /dev/null
	@echo "$(PINK)=== 🚮Minishell clean succeed. $(END)\n"

fclean:clean
	@rm -rf $(NAME) $(BINDIR) $(TMPDIR)
	@make fclean -C ${LIBFT_DIR} > /dev/null
	@echo "$(PINK)=== 🔁Minishell fclean succeed. $(END)\n"

mac:all clean

re: fclean all

.PHONY: all clean fclean mac re
