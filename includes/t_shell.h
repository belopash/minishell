/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:42:15 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/20 15:40:32 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SHELL_H
#define T_SHELL_H

#include "./libft.h"
#include "./t_env.h"
#include "./t_builtin.h"

typedef struct s_shell
{
	int in;
	int out;
	int waiting;
	t_env *env;
	t_builtins_manager *builtins;
	int (*start)(struct s_shell *);
	void (*destroy)(struct s_shell *);
    int code;
} t_shell;

t_shell *new_shell(char **env, t_builtin *builtins);

#endif
