/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_commands.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:24:32 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/07 19:44:18 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_COMMANDS_H
# define BUILDIN_COMMANDS_H

# include <linux/limits.h>

int ft_echo(char **args, char** env);
int ft_pwd(char **args, char** env);
int ft_cd(char **args, char **env);

#endif