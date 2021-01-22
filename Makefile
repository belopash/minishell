# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/22 14:55:03 by ashea             #+#    #+#              #
#    Updated: 2021/01/22 19:57:15 by bbrock           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
NAME_LIB = libft.a
COMPIL = gcc -Wall -Wextra -Werror -g ./srcs/main.c ./srcs/*/ft_*.c ./libft.a -I ./includes/
FLAGS = -Wall -Wextra -Werror
INCS = ./includes/
HDRS = libft.h
REMOVE = rm -f
SRCS=./lib/libft/ft_bzero.c ./lib/libft/ft_memccpy.c ./lib/libft/ft_memcpy.c ./lib/libft/ft_memmove.c ./lib/libft/ft_memset.c ./lib/libft/ft_memchr.c \
./lib/libft/ft_memcmp.c ./lib/libft/ft_strlen.c ./lib/libft/ft_strlcpy.c ./lib/libft/ft_strlcat.c ./lib/libft/ft_strchr.c ./lib/libft/ft_strrchr.c \
./lib/libft/ft_strnstr.c ./lib/libft/ft_strncmp.c ./lib/libft/ft_atoi.c ./lib/libft/ft_isalpha.c ./lib/libft/ft_isdigit.c ./lib/libft/ft_isalnum.c \
./lib/libft/ft_isascii.c ./lib/libft/ft_isprint.c ./lib/libft/ft_toupper.c ./lib/libft/ft_tolower.c ./lib/libft/ft_calloc.c ./lib/libft/ft_strdup.c \
./lib/libft/ft_substr.c ./lib/libft/ft_strjoin.c ./lib/libft/ft_strtrim.c ./lib/libft/ft_split.c ./lib/libft/ft_itoa.c ./lib/libft/ft_strmapi.c \
./lib/libft/ft_putchar_fd.c ./lib/libft/ft_putstr_fd.c ./lib/libft/ft_putendl_fd.c ./lib/libft/ft_putnbr_fd.c ./lib/libft/get_next_line.c ./lib/libft/get_next_line_utils.c \
./lib/libft/ft_lstnew.c ./lib/libft/ft_lstadd_front.c ./lib/libft/ft_lstsize.c ./lib/libft/ft_lstlast.c ./lib/libft/ft_lstadd_back.c ./lib/libft/ft_lstdelone.c \
./lib/libft/ft_lstclear.c ./lib/libft/ft_lstiter.c ./lib/libft/ft_lstmap.c
OBJ = $(SRCS:.c=.o)

%.o: %.c $(HDRS)

all: $(NAME_LIB) $(NAME)

$(NAME_LIB): $(OBJ)
	ar rc $(NAME_LIB) $^
	ranlib $(NAME_LIB)
	echo "Done!"

$(NAME):
	$(COMPIL) -o $(NAME)

clean:
	$(REMOVE) $(OBJ)

fclean: clean
	$(REMOVE) $(NAME_LIB) $(NAME)

re: fclean all