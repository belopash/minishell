/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:20:44 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/18 12:09:50 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/t_buildin.h"
#include "../includes/buildins.h"
#include <unistd.h>
#include "../includes/libft.h"

t_buildin *find_buildin(char *name)
{
	static t_buildin buildins[] = {
		(t_buildin){"echo", ft_echo},
		(t_buildin){"cd", ft_cd},
		(t_buildin){"pwd", ft_pwd},
		(t_buildin){"env", ft_env},
		(t_buildin){"export", ft_export},
		(t_buildin){"unset", ft_unset},
		{0, 0}};
	int i = 0;

	while (buildins[i].name)
	{
		if (!ft_strncmp(name, buildins[i].name, ft_strlen(name)))
			return &buildins[i];
		i++;
	}
	return NULL;
}

int execbi(t_shell *shell, char **args)
{
	t_buildin *buildin;

	if (!(buildin = find_buildin(args[0])))
		return -1;

	exit(buildin->command(shell, args));
}