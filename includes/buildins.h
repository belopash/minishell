/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:24:32 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/10 19:07:52 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_COMMANDS_H
# define BUILDIN_COMMANDS_H

# include <limits.h>

int ft_echo(char **args, char** env);
int ft_pwd(char **args, char** env);
int ft_cd(char **args, char **env);
int ft_env(char **args, char **env);

#endif
