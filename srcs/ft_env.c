/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:56:38 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/11 19:50:41 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/t_shell.h"

int ft_env(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	(void)args;
	while (shell->env[i])
	{
		ft_putendl_fd(shell->env[i++], 1);
		i++;
	}
	return (0);
}