/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 14:05:39 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:54:31 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*elem;

	if (!lst || !f || !(newlst = ft_lstnew(f(lst->content))))
		return (NULL);
	elem = newlst;
	lst = lst->next;
	while (lst)
	{
		if (!(elem->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&newlst, del);
		}
		elem = elem->next;
		lst = lst->next;
	}
	return (newlst);
}
