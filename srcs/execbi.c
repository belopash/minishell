/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:20:44 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/08 13:53:39 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/t_buildin.h"
#include "../includes/buildin_commands.h"
#include <unistd.h>
#include "../includes/libft.h"

static t_buildin *find_buildin(char *name)
{
	static t_buildin buildins[] = {
		(t_buildin){"echo", ft_echo},
		(t_buildin){"cd", ft_cd},
		(t_buildin){"pwd", ft_pwd},
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

int execbi(char *name, char **args, char **envp)
{
	t_buildin *buildin;

	if (!(buildin = find_buildin(name)))
		return -1;

	return buildin->command(args, envp);
}