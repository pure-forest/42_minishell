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

LEXER=lexer.c lexer_utils.c lexer_text_quote.c lexer_reprocess_token.c \
	lexer_pipe_redir.c remove_quotes.c remove_quotes_utils.c
PARSER= parser.c parser_utils.c handle_heredoc.c
BUILTIN=cd.c echo.c export_utils.c export.c pwd.c unset.c env.c
EXECUTE= create_env.c create_export.c env_export_utils.c \
		node_utils.c error_handling.c string_utils.c
EXPANSION= expand_dollar_sign.c
MINISHEL=main.c

SRC=$(addprefix ${SRCDIR}/, $(MINISHEL)) \
	$(addprefix ${SRCDIR}/lexer/, $(LEXER)) \
	$(addprefix $(SRCDIR)/parser/, $(PARSER)) \
	$(addprefix $(SRCDIR)/execution/, $(EXECUTE)) \
	$(addprefix $(SRCDIR)/execution/builtins/, $(BUILTIN)) \
	$(addprefix $(SRCDIR)/expansion/, $(EXPANSION))

OBJ=${SRC:${SRCDIR}%.c=${OBJDIR}/%.o}

all:$(LIBFT_A) $(BINDIR)/${NAME}



${LIBFT_A}:
	@make -C ${LIBFT_DIR} > /dev/null
	@echo "$(PINK)=== ✅Libft compile succeed.  $(END)\n"

$(GNL):
	@make -C $(GNL_DIR) > /dev/null
	@echo "$(PINK)=== ✅Get next line comiple succeed $(END)\n"

${OBJDIR}:
	@mkdir -p obj

$(BINDIR):
	@mkdir -p bin

$(TMPDIR):
	@mkdir -p tmp

${OBJDIR}/%.o:${SRCDIR}/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -o $@ -c $<

$(BINDIR)/${NAME}:$(LIBFT_A) ${OBJ} | $(BINDIR) $(TMPDIR)
	@$(CC) $(OBJ) $(LIBFT_A) \
	-lreadline \
	-o $(BINDIR)/$(NAME)
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
