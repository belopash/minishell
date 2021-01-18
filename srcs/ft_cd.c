/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:50:29 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/18 20:52:46 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/t_builtin.h"
#include "../includes/t_shell.h"
#include <limits.h>
#ifndef PATH_MAX
#include <linux/limits.h>
#endif

int ft_cd(t_builtin *builtin, char **args)
{
	char path[PATH_MAX];
	char *t;

	if (!getcwd(path, PATH_MAX))
		return (-1);
	if (!(t = ft_strjoin("OLDPWD=", path)))
		return (-1);
	builtin->shell->env->add(builtin->shell->env, t);
	free(t);
	if (chdir(args[1]) < 0)
		return (-1);
	if (!getcwd(path, PATH_MAX))
		return (-1);
	if (!(t = ft_strjoin("PWD=", path)))
		return (-1);
	builtin->shell->env->add(builtin->shell->env, t);
	free(t);
	return (0);
}