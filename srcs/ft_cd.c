/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:50:29 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/20 18:57:13 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/t_builtin.h"
#include "../includes/t_shell.h"
#include "../includes/utils.h"
#include <errno.h>
#include <limits.h>
#ifndef PATH_MAX
#include <linux/limits.h>
#endif

static int error(char *error)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putendl_fd(error, 2);
	return (1);
}

int ft_cd(t_builtin *builtin, char **args)
{
	char path[PATH_MAX];
	char *t;

	if (ft_arrlen(args) > 2)
		return (error("too many arguments"));
	if (!getcwd(path, PATH_MAX))
		return (error(strerror(errno)));
	if (!(t = ft_strjoin("OLDPWD=", path)))
		return (error(strerror(errno)));
	builtin->shell->env->add(builtin->shell->env, t);
	free(t);
	if (chdir(args[1]) < 0)
		return (error(strerror(errno)));
	if (!getcwd(path, PATH_MAX))
		return (error(strerror(errno)));
	if (!(t = ft_strjoin("PWD=", path)))
		return (error(strerror(errno)));
	builtin->shell->env->add(builtin->shell->env, t);
	free(t);
	return (0);
}