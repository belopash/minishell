/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_other_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:44:20 by ashea             #+#    #+#             */
/*   Updated: 2021/01/22 21:32:03 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	ft_screening(int *j, char *content, char *line)
{
	if (line[0] == '\\' || line[0] == '\'' || line[0] == '"' ||
			line[0] == '$' || line[0] == ';' || line[0] == '|' ||
			line[0] == '>' || line[0] == '<')
	{
		content[*j] = line[0];
		(*j)++;
		return (1);
	}
	return (0);
}

int			ft_if_other_char(int *j, char *content, char *line)
{
	int		i;

	i = 0;
	if (line[i] == ' ')
	{
		i++;
		return (i);
	}
	if (line[i] == '\\')
	{
		i += 1 + ft_screening(j, content, line + 1);
		return (i);
	}
	if (line[i] != ' ' && line[i] != '\0' && line[i] != '\'' &&
			line[i] != '"' && line[i] != ';' && line[i] != '|' &&
			line[i] != '>' && line[i] != '<')
	{
		content[*j] = line[i];
		(*j)++;
		i++;
	}
	return (i);
}
