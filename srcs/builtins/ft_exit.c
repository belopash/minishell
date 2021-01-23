/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:25:44 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/23 14:07:51 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/t_shell.h"
#include "../includes/utils.h"

int	ft_isnumber(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1 && i);
}

int	ft_exit(t_builtin *builtin, char **args)
{
	int code;

	ft_putendl_fd("exit", builtin->shell->out);
	if (ft_arrlen((void **)args) == 1)
		exit(builtin->shell->code);
	if (!ft_isnumber(args[1]))
		exit(error("exit", "numeric argument required", 2));
	code = ft_atoi(args[1]);
	if (ft_arrlen((void **)args) > 2)
		exit(error("exit", "too many arguments", code));
	exit(code);
	return (0);
}
