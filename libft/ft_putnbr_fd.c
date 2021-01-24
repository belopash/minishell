/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 11:55:49 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:55:38 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	itoc(int n)
{
	if (n / 10 != 0)
		return ('0');
	n = (n < 0) ? -n : n;
	return ('0' + n);
}

void			ft_putnbr_fd(int n, int fd)
{
	if (n / 10 != 0)
		ft_putnbr_fd(n / 10, fd);
	else if (n < 0)
		ft_putchar_fd('-', fd);
	ft_putchar_fd(itoc(n % 10), fd);
}
