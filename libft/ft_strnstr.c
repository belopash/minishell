/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 22:32:35 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:57:47 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *find, size_t len)
{
	size_t i;
	size_t flen;

	i = 0;
	if (!find[0])
		return ((char *)s);
	flen = ft_strlen(find);
	while (s[i] && len - i >= flen)
	{
		if (ft_strncmp(&s[i], find, flen) == 0)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
