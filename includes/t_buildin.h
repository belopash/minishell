/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_buildin.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:18:01 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/18 12:01:41 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_BUILIN_H
#define T_BUILIN_H

#include "t_shell.h"

typedef struct s_buildin
{
    char *name;
    int (*command)(t_shell *shell, char **argv);
} t_buildin;

int execbi(t_shell *shell, char **args);
t_buildin *find_buildin(char *name);

#endif