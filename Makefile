# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/22 14:55:03 by ashea             #+#    #+#              #
#    Updated: 2021/01/22 14:55:12 by ashea            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
COMPIL = gcc main.c ./srcs/*/*.c ./lib/*.a -I ./includes/

all: $(NAME)

$(NAME):
	$(COMPIL) -o $(NAME)

clean:
	rm $(NAME)

re: clean $(NAME)