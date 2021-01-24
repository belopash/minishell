# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/22 14:55:03 by ashea             #+#    #+#              #
#    Updated: 2021/01/22 14:57:29 by bbrock           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror
INCS = ./
HDRS = libft.h
SRCS=ft_bzero.c ft_memccpy.c ft_memcpy.c ft_memmove.c ft_memset.c ft_memchr.c \
ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c get_next_line_utils.c \
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $^
	@ranlib $(NAME)

%.o: %.c $(HDRS)
	@gcc $(FLAGS) -I$(INCS) -c $<

clean:
	@/bin/rm -f $(OBJ) $(BNS_OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
