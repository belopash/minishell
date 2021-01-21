/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:50:29 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/21 19:14:37 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/t_builtin.h"
#include "../includes/t_shell.h"
#include "../includes/utils.h"
#include <errno.h>
#include <limits.h>
#ifndef PATH_MAX
# include <linux/limits.h>
#endif

int ft_cd(t_builtin *builtin, char **args)
{
	char path[PATH_MAX];
	char *t;

	if (ft_arrlen(args) > 2)
		return (error("cd", "too many arguments"));
	if (!getcwd(path, PATH_MAX))
		return (error("cd", strerror(errno)));
	if (!(t = ft_strjoin("OLDPWD=", path)))
		return (error("cd", strerror(errno)));
	builtin->shell->env->add(builtin->shell->env, t);
	free(t);
	if (chdir(args[1]) < 0)
		return (error("cd", strerror(errno)));
	if (!getcwd(path, PATH_MAX))
		return (error("cd", strerror(errno)));
	if (!(t = ft_strjoin("PWD=", path)))
		return (error("cd", strerror(errno)));
	builtin->shell->env->add(builtin->shell->env, t);
	free(t);
	return (0);
}