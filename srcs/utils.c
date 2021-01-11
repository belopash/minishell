/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:18:42 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/11 18:25:41 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_getenv(const char *name, char **env)
{
	char *env_var;
	int i;

	i = 0;
	env_var = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name)))
		{
			return env[i];
		}
		i++;
	}
	return (NULL);
}

char *ft_pathjoin(char *path1, char *path2)
{
	char *path;
	char *t;

	if (!(t = ft_strjoin(path1, "/")))
		return (NULL);
	if (!(path = ft_strjoin(t, path2)))
		return (NULL);
	free(t);
	return path;
}

char **ft_toarray(t_list *list)
{
	int i;
	char **argv;
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