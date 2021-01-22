/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:18:42 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 11:29:01 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pathjoin(char *path1, char *path2)
{
	char	*path;
	char	*t;

	if (!(t = ft_strjoin(path1, "/")))
		return (NULL);
	if (!(path = ft_strjoin(t, path2)))
		return (NULL);
	free(t);
	return (path);
}

char	**ft_toarray(t_list *list)
{
	int		i;
	char	**argv;

	i = 0;
	argv = (char **)malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	while (list)
	{
		argv[i] = list->content;
		list = list->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

t_list	*ft_tolist(char **arr)
{
	int		i;
	t_list	*list;
	char	*content;
	t_list	*t;

	i = 0;
	list = NULL;
	while (arr[i])
	{
		if (!(content = ft_strdup(arr[i])))
			return (NULL);
		if (!(t = ft_lstnew(content)))
			return (NULL);
		ft_lstadd_back(&list, t);
		i++;
	}
	return (list);
}

int		ft_arrlen(void **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int		error(char *name, char *error, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
	return (code);
}
