# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marjorie <marjorie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/28 10:01:49 by daniefe2          #+#    #+#              #
#    Updated: 2025/08/05 11:12:19 by marjorie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_bzero.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strlcpy.c \
		ft_tolower.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_memcpy.c \
		ft_memset.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_toupper.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c

CC = cc

FLAGS = -Wall -Wextra -Werror -I.

AR = ar rc

NAME = libft.a

RM = rm -rf

OBJECT = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	$(AR) $(NAME) $(OBJECT)

%.o: %.c
	$(CC) $(FLAGS) -g -c $< -o $@

clean:
	$(RM) $(OBJECT)

fclean:	clean
	$(RM) $(NAME)

re: fclean all