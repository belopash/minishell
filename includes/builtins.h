/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:24:32 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/18 20:58:35 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef builtin_COMMANDS_H
#define builtin_COMMANDS_H


#include "t_builtin.h"

int ft_echo(t_builtin *builtin, char **args);
int ft_pwd(t_builtin *builtin, char **args);
int ft_cd(t_builtin *builtin, char **args);
int ft_env(t_builtin *builtin, char **args);
int ft_export(t_builtin *builtin, char **args);
int ft_unset(t_builtin *builtin, char **args);
int execbi(t_builtin *builtin, char **args);

#endif