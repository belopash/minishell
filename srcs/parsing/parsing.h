/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:09:41 by ashea             #+#    #+#             */
/*   Updated: 2021/01/22 12:09:50 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../includes/t_command.h"
#include "../includes/t_shell.h"
#include "../includes/t_builtin.h"
#include "../includes/builtins.h"
#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/utils.h"
#include <limits.h>
#ifndef PATH_MAX
#include <linux/limits.h>
#endif
#include <errno.h>

int ft_parsing(t_shell *shell, char *line);
void ft_add_arg(int *j, char **content, t_command *command);
int ft_if_next_command(int *i, char *line, t_command **command, t_shell *shell);
int ft_if_pipe(int *i, char *line, t_command **command, t_shell *shell);
int ft_if_redirect(int *i, char *line, t_command *command, t_shell *shell);
int ft_if_env(int *j, char *content, char *line, t_shell *shell);
int ft_if_double_quotes(int *j, char *content, char *line, t_shell *shell);
int ft_if_single_quotes(int *j, char *content, char *line, t_shell *shell);
int ft_if_other_char(int *j, char *content, char *line, t_shell *shell);




#endif

