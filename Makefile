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


NAME = minishell
COMPIL = gcc -Wall -Wextra -Werror ./srcs/main.c ./srcs/*/*.c ./lib/*.a -I ./includes/

all: $(NAME)

$(NAME):
	$(COMPIL) -o $(NAME)

clean:
	rm $(NAME)

re: clean $(NAME)