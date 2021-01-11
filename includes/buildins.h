/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:24:32 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/11 12:43:12 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_COMMANDS_H
#define BUILDIN_COMMANDS_H

#include <limits.h>
#ifndef PATH_MAX
#include <linux/limits.h>
#endif
int ft_echo(char **args, char **env);
int ft_pwd(char **args, char **env);
int ft_cd(char **args, char **env);
int ft_env(char **args, char **env);

#endif