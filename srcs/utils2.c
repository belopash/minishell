/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:44:41 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/21 19:45:13 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int			print_name(void)
{
	write(1, "\e[1;34mminishell\e[0m$> ", 23);
	return (0);
}

void		putnlandname(void)
{
	write(1, "\n", 1);
	print_name();
}

void		del(void)
{
	write(1, "\b \b", 3);
	write(1, "\b \b", 3);
}
