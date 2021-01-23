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

NAME		= minishell
FLAGS		= -g -Wall -Wextra -Werror
HEADERS		= includes/

SRCS = srcs/main.c \
srcs/builtins/ft_cd.c    srcs/builtins/ft_export.c  srcs/objects/ft_builtins_manager.c  srcs/objects/ft_shell.c             srcs/parsing/ft_if_next_command.c  srcs/parsing/ft_if_single_quotes.c \
srcs/builtins/ft_echo.c  srcs/builtins/ft_pwd.c     srcs/objects/ft_command2.c          srcs/parsing/ft_add_arg.c           srcs/parsing/ft_if_other_char.c    srcs/parsing/ft_parsing.c \
srcs/builtins/ft_env.c   srcs/builtins/ft_unset.c   srcs/objects/ft_command.c           srcs/parsing/ft_if_double_quotes.c  srcs/parsing/ft_if_pipe.c          srcs/utils/ft_utils2.c \
srcs/builtins/ft_exit.c  srcs/objects/ft_builtin.c  srcs/objects/ft_env.c               srcs/parsing/ft_if_env.c            srcs/parsing/ft_if_redirect.c      srcs/utils/ft_utils.c

OBJS	= $(SRCS:.c=.o)
LIBFT 	= libft/libft.a

all: $(NAME)

$(NAME) : 	$(LIBFT) $(OBJS) $(HEADERS)
			gcc $(FLAGS) -I $(HEADERS) $(OBJS) $(LIBFT) -lncurses -o $(NAME)

$(LIBFT):
			make -C libft


%.o: %.c
			$(BUILD_PRINT)
			gcc -g $(FLAGS) -I $(HEADERS) -c $< -o $@

clean:
			$(MAKE) -C libft/ clean
			rm -f $(OBJS)

fclean: 	clean
			$(MAKE) -C libft/ fclean
			rm -f $(NAME)

re: fclean all
.PHONY: all fclean clean re
