/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:50:29 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/14 19:25:45 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/buildins.h"
#include "../includes/t_shell.h"

int ft_cd(t_shell *shell, char **args)
{
	char path[PATH_MAX];
	char *t;

	if (!getcwd(path, PATH_MAX))
		return (-1);
	if (!(t = ft_strjoin("OLDPWD=", path)))
		return (-1);
	shell->add_env(shell, t);
	free(t);
	if (chdir(args[1]) < 0)
		return (-1);
	if (!getcwd(path, PATH_MAX))
		return (-1);
	if (!(t = ft_strjoin("PWD=", path)))
		return (-1);
	shell->add_env(shell, t);
	free(t);
	return (0);
}