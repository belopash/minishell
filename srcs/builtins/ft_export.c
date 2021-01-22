/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:16:49 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 14:50:13 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/t_shell.h"
#include "../includes/utils.h"

static int	ft_isvalid(char *env)
{
	int i;

	i = 0;
	while (env[i] != '=')
	{
		if (env[i] != '_' && !ft_isalnum(env[i]))
			return (0);
	}
	return (1 && i);
}

int			ft_export(t_builtin *builtin, char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		if (!ft_isvalid(args[i]))
			return (error("export", "not a valid identifier", 1));
	}
	i = 1;
	while (args[i])
	{
		if (!ft_strchr(args[i], '='))
			continue ;
		if (!builtin->shell->env->add(builtin->shell->env, args[i]))
			return (1);
	}
	return (0);
}
