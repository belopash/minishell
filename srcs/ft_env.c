/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:56:38 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/10 19:09:01 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int ft_env(char **args, char** env)
{
	int	i;

	i = 0;
	(void)args;
	while (env[i])
	{
		ft_putendl_fd((char*)env[i++], 1);
		i++;
	}
	return (0);
}