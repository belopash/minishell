/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:24:32 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/11 19:49:58 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_COMMANDS_H
#define BUILDIN_COMMANDS_H

#include <limits.h>
#ifndef PATH_MAX
#include <linux/limits.h>
#endif
#include "t_shell.h"

int ft_echo(t_shell *shell, char **args);
int ft_pwd(t_shell *shell, char **args);
int ft_cd(t_shell *shell, char **args);
int ft_env(t_shell *shell, char **args);
int execbi(t_shell *shell, char **args);

#endif