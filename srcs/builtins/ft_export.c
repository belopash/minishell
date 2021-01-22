/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:16:49 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 12:55:28 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/t_shell.h"

int	ft_export(t_builtin *builtin, char **args)
{
	if (!ft_strchr(args[1], '='))
		return (-1);
	if (!builtin->shell->env->add(builtin->shell->env, args[1]))
		return (-1);
	return (0);
}
