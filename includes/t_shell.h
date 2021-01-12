/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:42:15 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/12 12:04:29 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SHELL_H
#define T_SHELL_H

#include "libft.h"

typedef struct s_shell
{
	int in;
	int out;
	int waiting;
	t_list *env;
	int (*start)(struct s_shell *);
	char *(*getenv)(struct s_shell *, char *);
} t_shell;

t_shell *newShell(char **env);

#endif