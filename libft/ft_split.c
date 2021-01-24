/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 11:58:16 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:55:49 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_clear2(char **ar, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
		free(ar[i++]);
	free(ar);
}

static	size_t	count(char const *s, char c)
{
	size_t n;

	n = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			n++;
		s++;
	}
	return ((n) ? n : 1);
}

char			**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**new;

	if (!s || !(new = (char **)ft_calloc(count(s, c) + 1, sizeof(char *))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			j = 0;
			while (s[j] && s[j] != c && s[j] != '\0')
				j++;
			if (!(new[i++] = ft_substr(s, 0, j)))
			{
				ft_clear2(new, i - 1);
				return (NULL);
			}
			s += j - 1;
		}
		s++;
	}
	new[i] = NULL;
	return (new);
}
