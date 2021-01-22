/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:20:44 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/21 19:37:00 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/t_builtin.h"
#include <unistd.h>
#include "../includes/libft.h"

static void	destroy(t_builtin *builtin)
{
	if (!builtin)
		return ;
	ft_bzero(builtin, sizeof(t_builtin));
	free(builtin);
}

static void	constructor(t_builtin *builtin, t_shell *shell, char *name,
						int (*command)(t_builtin *builtin, char **argv))
{
	builtin->shell = shell;
	builtin->name = name;
	builtin->command = command;
	builtin->destroy = destroy;
}

t_builtin	*new_builtin(t_shell *shell, char *name,
						int (*command)(t_builtin *builtin, char **argv))
{
	t_builtin *builtin;

	if (!(builtin = malloc(sizeof(t_builtin))))
		exit(1);
	constructor(builtin, shell, name, command);
	return (builtin);
}
