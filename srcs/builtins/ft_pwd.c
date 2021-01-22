/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:20:55 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 14:51:48 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include "../includes/libft.h"
#include "../includes/t_shell.h"
#include <limits.h>
#ifndef PATH_MAX
# include <linux/limits.h>
#endif

int	ft_pwd(t_builtin *builtin, char **args)
{
	char buf[PATH_MAX + 1];

	(void)builtin;
	(void)args;
	if (!getcwd(buf, PATH_MAX))
		return (1);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	return (0);
}
