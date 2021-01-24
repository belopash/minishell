/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 16:15:10 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:57:27 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (size > 0 && dst)
	{
		if (srclen + 1 < size)
			ft_memmove(dst, src, srclen + 1);
		else
		{
			ft_memmove(dst, src, size - 1);
			dst[size - 1] = '\0';
		}
	}
	return (srclen);
}
