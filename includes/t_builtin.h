/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_builtin.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:18:01 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/18 21:03:33 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_BUILTIN_H
#define T_BUILTIN_H

#include "./libft.h"

typedef struct s_shell t_shell;

typedef struct s_builtin
{
    char *name;
    int (*command)(struct s_builtin *, char **);
    t_shell *shell;
} t_builtin;

typedef struct s_builtins_manager
{
    t_list *list;
    t_builtin *(*get)(struct s_builtins_manager *, char *);
    t_shell *shell;
} t_builtins_manager;

t_builtin *new_builtin(t_shell *shell, char *name, int (*command)(t_builtin *builtin, char **argv));
t_builtins_manager *new_builtin_manager(t_shell *shell, t_builtin *builtins);

#endif