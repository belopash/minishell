/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:09:06 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 14:51:37 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../includes/libft.h"
#include "../includes/t_shell.h"

static bool	ft_isflags(char *flags, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(flags, str[i]))
			return (false);
		i++;
	}
	return (i && true);
}

int			ft_echo(t_builtin *builtin, char **args)
{
	int		i;
	bool	nonewline;

	(void)builtin;
	i = 1;
	nonewline = 0;
	while (args[i] && args[i][0] == '-')
	{
		if (ft_isflags(args[i], "n"))
			nonewline = nonewline | true;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!nonewline)
		write(1, "\n", 1);
	return (0);
}
