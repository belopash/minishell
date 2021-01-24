/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:26:12 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:51:10 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/t_env.h"
#include "../includes/utils.h"

static void	add(t_env *env, char *var)
{
	t_list	*item;
	int		namelen;

	namelen = ft_strlen(var);
	if (ft_strchr(var, '='))
		namelen = ft_strchr(var, '=') - var;
	item = env->list;
	while (item)
	{
		if (ft_strncmp(item->content, var, namelen) == 0
			&& (*(char *)(item->content + namelen) == '='
			|| *(char *)(item->content + namelen) == '\0'))
		{
			if (ft_strchr(var, '='))
			{
				free(item->content);
				if (!(item->content = ft_strdup(var)))
					exit(1);
			}
			return ;
		}
		item = item->next;
	}
	ft_lstadd_back(&(env->list), ft_lstnew(ft_strdup(var)));
}

static void	del(t_env *env, char *name)
{
	t_list	*item;
	t_list	*prev;
	int		namelen;

	namelen = ft_strlen(name);
	item = env->list;
	prev = NULL;
	while (item)
	{
		if (ft_strncmp(item->content, name, namelen) == 0
			&& (*(char *)(item->content + namelen) == '='
			|| *(char *)(item->content + namelen) == '\0'))
		{
			if (prev)
				prev->next = item->next;
			else
				env->list = item->next;
			ft_lstdelone(item, free);
			item = NULL;
			return ;
		}
		prev = item;
		item = item->next;
	}
}

static char	*get(t_env *env, char *name)
{
	t_list	*item;
	int		namelen;

	namelen = ft_strlen(name);
	item = env->list;
	while (item)
	{
		if (ft_strncmp(item->content, name, namelen) == 0
			&& (*(char *)(item->content + namelen) == '='))
			return (item->content + namelen + 1);
		item = item->next;
	}
	return (NULL);
}

static void	destroy(t_env *env)
{
	if (!env)
		return ;
	ft_bzero(env, sizeof(t_env));
	free(env);
}

t_env		*new_env(char **envs)
{
	t_env *env;

	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	env->list = ft_tolist(envs);
	env->del = del;
	env->add = add;
	env->get = get;
	env->destroy = destroy;
	return (env);
}
