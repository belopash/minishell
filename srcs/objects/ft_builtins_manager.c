/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:20:44 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/21 19:39:07 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/t_builtin.h"
#include <unistd.h>
#include "../includes/libft.h"

static t_builtin	*get(t_builtins *builtins_manager, char *name)
{
	t_list *item;

	item = builtins_manager->list;
	while (item)
	{
		if (ft_strncmp(((t_builtin *)item->content)->name, name,
						ft_strlen(name) + 1) == 0)
			return (item->content);
		item = item->next;
	}
	return (NULL);
}

static void			destroy(t_builtins *builtins_manager)
{
	if (!builtins_manager)
		return ;
	ft_bzero(builtins_manager, sizeof(t_builtins));
	free(builtins_manager);
}

static void			constructor(t_builtins *builtins_manager,
								t_shell *shell, t_builtin *builtins)
{
	int		i;
	t_list	*t;

	i = 0;
	builtins_manager->shell = shell;
	builtins_manager->list = NULL;
	while (builtins[i].name)
	{
		if (!(t = ft_lstnew(new_builtin(shell, builtins[i].name,
										builtins[i].command))))
			exit(1);
		ft_lstadd_back(&(builtins_manager->list), t);
		i++;
	}
	builtins_manager->get = get;
	builtins_manager->destroy = destroy;
}

t_builtins			*new_builtins(t_shell *shell, t_builtin *builtins)
{
	t_builtins *builtins_manger;

	if (!(builtins_manger = malloc(sizeof(t_builtins))))
		exit(1);
	constructor(builtins_manger, shell, builtins);
	return (builtins_manger);
}
