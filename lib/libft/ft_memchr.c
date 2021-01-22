/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 14:06:13 by bbrock            #+#    #+#             */
/*   Updated: 2020/05/10 15:40:19 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	t_byte	*s;
	size_t	i;

	s = (t_byte *)arr;
	i = 0;
	while (i < n)
	{
		if (s[i] == (t_byte)c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}
