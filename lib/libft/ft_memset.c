/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 10:42:32 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:55:19 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int c, size_t n)
{
	t_byte	*s;
	size_t	i;

	s = (t_byte *)buf;
	i = 0;
	while (i < n)
	{
		s[i] = (t_byte)c;
		i++;
	}
	return (buf);
}
