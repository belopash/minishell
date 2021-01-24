/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:16:05 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:57:17 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(new = (char *)ft_calloc(len1 + len2 + 1, sizeof(char))))
		return (NULL);
	ft_strlcpy(new, s1, len1 + len2 + 1);
	ft_strlcat(new, s2, len1 + len2 + 1);
	return (new);
}
