/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_double_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:31:42 by ashea             #+#    #+#             */
/*   Updated: 2021/01/22 13:57:24 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static void		ft_if_not_closed_quotes(int *j, t_command *command)
{
	write(2, "Error: quote not closed\n", 24);
	(*j) = 0;
	command->shell->code = 1;
}

static int		ft_if_double_quotes_dop(int *j, char *content,
		char *line, t_command *command)
{
	int			i;
	int			delta;

	i = 0;
	while (line[i] != '"' && line[i])
	{
		if ((delta = ft_if_env(j, content, line + i, command)) > 0)
		{
			i += delta;
			continue;
		}
		if (line[i] == '\\' && (line[i + 1] == '\\' ||
					line[i + 1] == '$' || line[i + 1] == '"'))
			i++;
		content[*j] = line[i];
		(*j)++;
		i++;
	}
	return (i);
}

static int		ft_if_empty_double_quotes(int *i, int *j,
		char *content, char *line)
{
	if (line[*i] == '"' && (line[*i + 1] == '\0' || line[*i + 1] == ' ' ||
				line[*i + 1] == '>' || line[*i + 1] == '<' ||
				line[*i + 1] == ';' || line[*i + 1] == '|'))
	{
		content[*j] = '\0';
		(*j)++;
		(*i)++;
		return (1);
	}
	return (0);
}

int				ft_if_double_quotes(int *j, char *content,
		char *line, t_command *command)
{
	int			i;

	i = 0;
	if (line[i] == '"')
	{
		i++;
		if (ft_if_empty_double_quotes(&i, j, content, line))
			return (i);
		i += ft_if_double_quotes_dop(j, content, line + i, command);
		if (line[i] == '\0')
			ft_if_not_closed_quotes(j, command);
		i++;
	}
	return (i);
}
