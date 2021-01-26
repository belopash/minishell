/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:09:41 by ashea             #+#    #+#             */
/*   Updated: 2021/01/26 17:06:31 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "./t_command.h"
# include "./t_shell.h"
# include "./t_builtin.h"
# include "./builtins.h"
# include "./minishell.h"
# include "./libft.h"
# include "./utils.h"
# include <limits.h>
# ifndef PATH_MAX
#  include <linux/limits.h>
# endif
# include <errno.h>

int		ft_parsing(t_shell *shell, char *line);
void	ft_add_arg(int *j, char *content, t_command *command);
int		ft_if_next_command(int *i, char *line, t_command **command);
int		ft_if_pipe(int *i, char *line, t_command **command);
int		ft_if_redirect(int *i, char *line, t_command *command);
int		ft_if_env(int *j, char *content, char *line, t_command *command);
int		ft_if_double_quotes(int *j, char *content, char *line,
		t_command *command);
int		ft_if_single_quotes(int *j, char *content, char *line,
		t_command *command);
int		ft_if_other_char(int *j, char *content, char *line);

#endif
