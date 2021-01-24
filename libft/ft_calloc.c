/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 16:01:19 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:53:14 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	t_byte *new;

	if (!(new = malloc(size * num)))
		return (NULL);
	ft_bzero(new, num * size);
	return ((void *)new);
}
