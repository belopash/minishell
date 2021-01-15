/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:56:38 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/15 14:51:22 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/t_shell.h"

int ft_env(t_shell *shell, char **args)
{
	t_list *item;

	item = shell->env->list;
	(void)args;
	while (item)
	{
		ft_putendl_fd(item->content, 1);
		item = item->next;
	}
	return (0);
}