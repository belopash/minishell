/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:32:20 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:58:26 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy_gnl(void *dst, const void *src, size_t n)
{
	t_byte	*s_dst;
	t_byte	*s_src;
	size_t	i;

	if (!dst || !src)
		return (NULL);
	s_dst = (t_byte *)dst;
	s_src = (t_byte *)src;
	i = 0;
	while (i < n)
	{
		s_dst[i] = s_src[i];
		i++;
	}
	return (dst);
}

long	ft_strclen_gnl(const char *str, int c)
{
	long i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	if (!s2)
		return (NULL);
	len1 = ft_strclen_gnl(s1, '\0');
	len2 = ft_strclen_gnl(s2, '\0');
	if (!(new = (char *)malloc((len1 + len2 + 1) * sizeof(char))))
		return (NULL);
	ft_memcpy_gnl(new, s1, len1);
	ft_memcpy_gnl(new + len1, s2, len2 + 1);
	return (new);
}

void	ft_free_gnl(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
