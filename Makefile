# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 13:59:43 by daniefe2          #+#    #+#              #
#    Updated: 2025/06/29 16:38:56 by mrosset          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		:= minishell

# === Compilation ===
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -Iinclude -Ilib/Libft -g3

# === Sources & Objects ===
SRCS		:= $(shell find . -name "*.c" ! -path "./lib/Libft/*")
OBJS		:= $(SRCS:.c=.o)

# === Libft ===
LIBFT_DIR	:= lib/Libft
LIBFT_A		:= $(LIBFT_DIR)/libft.a

# === Rules ===

all:	$(LIBFT_A) $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
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
#valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes --track-fds=yes ./minishell
	valgrind -s --leak-check=full --log-file=valgrind.log --show-leak-kinds=all --track-fds=all --default-suppressions=yes --suppressions=.valgrind_readline ./$(NAME)

.PHONY: all clean fclean re