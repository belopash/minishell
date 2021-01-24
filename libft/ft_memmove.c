/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 10:42:43 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:55:13 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	t_byte *s_dst;
	t_byte *s_src;

	if (!dst && !src)
		return (NULL);
	s_dst = (t_byte *)dst;
	s_src = (t_byte *)src;
	if (s_dst < s_src || s_src + n < s_dst)
		return (ft_memcpy(dst, src, n));
	else
		while (n)
		{
			n--;
			s_dst[n] = s_src[n];
		}
	return (dst);
}
