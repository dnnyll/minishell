# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daniefe2 <daniefe2@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/28 10:01:49 by daniefe2          #+#    #+#              #
#    Updated: 2025/05/28 10:01:56 by daniefe2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := libft.a

CC      := cc
CFLAGS  := -Wall -Wextra -Werror

SRCS    := $(shell find . -name "*.c")
OBJS    := $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
