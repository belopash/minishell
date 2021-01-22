/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 10:42:17 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:54:51 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	t_byte	*s_dst;
	t_byte	*s_src;
	t_byte	s_c;
	size_t	i;

	if (dst == NULL && src == NULL)
		return (dst);
	s_dst = (t_byte *)dst;
	s_src = (t_byte *)src;
	s_c = (t_byte)c;
	i = 0;
	while (i < n)
	{
		s_dst[i] = s_src[i];
		if (s_src[i] == s_c)
			return (&s_dst[++i]);
		i++;
	}
	return (NULL);
}
