NAME		:= minishell

# === Compilation ===
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -I. -g
INCLUDES	= include

# === Sources & Objects ===
 SRCS = main.c \
 		builtins/builtins_utils.c \
		builtins/cd.c \
		builtins/echo_env_exit_utils.c \
		builtins/echo_env_exit.c \
		builtins/export.c \
		builtins/export_utils.c \
		builtins/pwd_unset.c \
 		environment_management/environment_handling.c \
		environment_management/environment_parsing.c \
		environment_management/environment_shlvl.c \
		executor/executor.c \
		executor/path_utils.c \
		executor/pipe.c \
		executor/redirections.c \
		executor/signals.c \
		executor/executor_utils.c \
		executor/check_command.c \
		executor/child_process_utils.c \
		heredoc/heredoc_fill.c \
 		heredoc/heredoc_temp.c \
		heredoc/heredoc_signal.c \
		heredoc/heredoc_utils.c \
 		initialization/init_data.c \
		lexer/lexer_quotes.c \
		lexer/lexer_utils.c \
		lexer/lexer.c \
		memory_management/free_commands.c \
		memory_management/free_data.c \
		memory_management/free_env.c \
 		memory_management/free_exit.c \
		memory_management/free_functions.c \
		memory_management/free_heredocs.c \
		memory_management/free_tokens.c \
		parser/parser_commands.c \
		parser/parser_fill_commands.c \
		parser/parser_pipe_handling.c \
		parser/parser_redirect_handling.c \
		parser/parser_validate_syntax_utils.c \
		parser/parser_validate_syntax.c \
		parser/parser_variable_handling.c \
		parser/parser_variable_utils.c \
		process_input/process_input.c \
 		tokens/tokens_expand.c \
		tokens/tokens.c \

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
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_A) -lreadline

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean:	clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f valgrind.log

re: fclean all

leaks:	all
	valgrind -s --leak-check=full --log-file=valgrind.log --show-leak-kinds=all --track-fds=all --default-suppressions=yes --suppressions=.valgrind_readline ./$(NAME)

.PHONY: all clean fclean re
