/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:28:45 by ashea             #+#    #+#             */
/*   Updated: 2021/01/23 11:19:45 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/libft.h"

static char	*ft_search_env(int *i, char *line, char **env)
{
	int		j;
	int		k;

	j = *i;
	while (line[*i] != ' ' && line[*i] != '$' && line[*i] != '"' &&
			line[*i] != '\'' && line[*i] != ';' && line[*i])
		(*i)++;
	k = 0;
	while (env[k])
	{
		if (!ft_strncmp(env[k], line + j, *i - j))
		{
			if (env[k][*i - j] == '=')
				return (ft_strdup(env[k] + *i - j + 1));
		}
		k++;
	}
	return (ft_strdup(""));
}

static void	ft_doublefree(void *a, void *b)
{
	free(a);
	free(b);
}

int			ft_if_env(int *j, char *content, char *line, t_command *command)
{
	int		i;
	int		k;
	char	*tmp;
	char	**t;

	i = 0;
	if (line[i] == '$' && ((line[i + 1] != '$' && line[i + 1] != '\\' &&
					line[i + 1] != ' ' && line[i + 1] != '\'' && line[i + 1]
					!= '"' && line[i + 1] != '\0') || line[i + 1] == '?'))
	{
		i++;
		t = ft_toarray(command->shell->env->list);
		if (line[i] == '?')
		{
			i++;
			if (!(tmp = ft_itoa(command->shell->code)))
				exit(-1);
		}
		else if (!(tmp = ft_search_env(&i, line, t)))
			exit(-1);
		k = 0;
		while(tmp[k])
		{
			if(tmp[k] == ' ' && *j > 0)
				ft_add_arg(j, content, command);
			if(tmp[k] != ' ') 
				content[(*j)++] = tmp[k];
			k++;
		}
		ft_doublefree(tmp, t);
	}
	return (i);
}
