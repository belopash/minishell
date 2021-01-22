/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:44:41 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:52:13 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int		print_name(void)
{
	write(1, "\e[1;34mminishell\e[0m$> ", 23);
	return (0);
}

void	putnlandname(int s)
{
	write(1, "\n", 1);
	print_name();
	(void)s;
}

void	delete(int s)
{
	write(1, "\b \b", 3);
	write(1, "\b \b", 3);
	(void)s;
}

void	ft_free2(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
