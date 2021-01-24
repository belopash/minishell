/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_single_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:43:07 by ashea             #+#    #+#             */
/*   Updated: 2021/01/22 14:01:23 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static void	ft_if_not_closed_quotes(int *j, t_command *command)
{
	write(2, "Error: quote not closed\n", 24);
	(*j) = 0;
	command->shell->code = 1;
}

static int	ft_if_empty_single_quotes(int *i, int *j, char *content, char *line)
{
	if (line[*i] == '\'' && (line[*i + 1] == '\0' || line[*i + 1] == ' '
				|| line[*i + 1] == '>' || line[*i + 1] == '<'
				|| line[*i + 1] == ';' || line[*i + 1] == '|'))
	{
		content[*j] = '\0';
		(*j)++;
		(*i)++;
		return (1);
	}
	return (0);
}

int			ft_if_single_quotes(int *j, char *content,
		char *line, t_command *command)
{
	int		i;

	i = 0;
	if (line[i] == '\'')
	{
		i++;
		if (ft_if_empty_single_quotes(&i, j, content, line))
			return (i);
		while (line[i] != '\'' && line[i])
		{
			content[*j] = line[i];
			(*j)++;
			i++;
		}
		if (line[i] == '\0')
			ft_if_not_closed_quotes(j, command);
		i++;
	}
	return (i);
}
