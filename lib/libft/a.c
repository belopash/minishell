/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 18:39:01 by dtanesha          #+#    #+#             */
/*   Updated: 2020/05/16 19:53:38 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static int ft_strlenc(char const *str, char end)
{
	int len;

	len = 0;
	while (*str && *str != end)
	{
		len++;
		str++;
	}
	return (len);
}

static int ft_cnt_word(char const *str, char delim)
{
	int cnt;

	cnt = 0;
	while (*str)
	{
		if (*str != delim)
		{
			cnt++;
			while (*str && *str != delim)
				str++;
		}
		str++;

	}
	return (cnt);
}

static char *ft_allocation(char const *str, char delim)
{
	char *word;

	word = ft_substr(str, 0, ft_strlenc(str, delim));
	return (word);
}

static char **free_list(char **list, int cnt)
{
	int i;

	i = 0;
	while (i < cnt)
	{
		free(list[i]);
		i++;
	}
	free(list);
	return (NULL);
}

char **ft_split(char const *s, char c)
{
	char **list;
	int cnter;

	if (s == NULL)
		return (NULL);
	list = NULL;
	cnter = 0;
	list = (char **)malloc(ft_cnt_word(s,c) * sizeof(char *));
		if (list == NULL)
			return (list);
	while (*s)
	{
		while(*s && *s == c)
			s++;
		if(*s && *s != c)
		{
			list[cnter] = ft_allocation(s,c);
			if (list[cnter] == NULL)
				return (free_list(list, cnter));
			cnter++;
			while (*s && *s != c)
				s++;
		}
	}
	list[cnter] = NULL;
	return (list);
}
int main ()
{

	char *str = "hello pidor kak je ya ustal godess     ";
	char **list;

	list = ft_split("lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultricies diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi.", 'i');
	while (*list != NULL)
		printf("%s\n",*list++);
	return (0);
}
