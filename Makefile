NAME		:= minishell

# === Compilation ===
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -I -g3
INCLUDES	= include

# === Sources & Objects ===
#SRCS		:= $(shell find . -name "*.c" ! -path "./lib/Libft/*")
 SRCS = main.c \
 		builtins/builtins_utils.c builtins/cd.c builtins/echo_env_exit.c builtins/export.c builtins/pwd_unset.c \
 		environment_management/environment_handling.c environment_management/environment_parsing.c \
 		executor/check_commands.c executor/executor.c executor/heredoc.c executor/path_utils.c executor/pipe.c executor/redirections.c executor/signals.c \
 		heredoc/heredoc_temp.c heredoc/heredoc_signal.c \
 		initialization/init_data.c \
 		lexer/extract_operator.c lexer/extract_quoted.c lexer/extract_word.c lexer/lexer.c \
 		memory_management/free_exit.c memory_management/free_functions.c \
 		parser/parser_commands.c parser/parser_fill_commands.c parser/parser_pipe_handling.c parser/parser_redirect_handling.c parser/parser_validate_syntax.c parser/parser_variable_handling.c \
 		printers/printers.c \
 		tokens/tokens_expand.c tokens/tokens.c \

OBJS		:= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -I$(LIBFT_DIR) -c $< -o $@

# === Libft ===
LIBFT_DIR	:= lib/Libft
LIBFT_A		:= $(LIBFT_DIR)/libft.a

# === Rules ===
all:	$(LIBFT_A) $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_A)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_A) -lreadline

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean:	clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f valgrind.log

re: fclean all

leaks:	all
#valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes --track-fds=yes ./minishell
	valgrind -s --leak-check=full --log-file=valgrind.log --show-leak-kinds=all --track-fds=all --default-suppressions=yes --suppressions=.valgrind_readline ./$(NAME)

.PHONY: all clean fclean re

# SRCS = main.c 
# 		builtins/builtins_utils.c builtins/cd.c builtins/echo_env_exit.c builtins/export.c builtins/pwd_unset.c
# 		environnement_management/environnement_handling.c environnement_management/environnement_parsing.c
# 		executor/check_commands.c executor/executor.c executor/heredoc.c executor/path_utils.c executor/pipe.c executor/redirections.c executor/signals.c
# 		heredoc/heredoc_temp.c
# 		initialization/init_data.c
# 		lexer/extract_operator.c lexer/extract_quoted.c lexer/extract_word.c lexer/lexer.c
# 		memory_management/free_exit.c memory_management/free_fonctions.c
# 		parser/parser_commands.c parser/parser_fill_commands.c parser/parser_pipe_handling.c parser/parser_redirect_handling.c parser/parser_validate_syntax.c parser/parser_validate_handling.c
# 		printers/printers.c
# 		tokens/tokens_expand.c token/tokens.c
