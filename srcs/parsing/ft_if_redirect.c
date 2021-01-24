/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:26:57 by ashea             #+#    #+#             */
/*   Updated: 2021/01/22 13:44:30 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	ft_redirect_l(int *i, char *line, t_command *command)
{
	if (line[*i] == '<')
	{
		(*i)++;
		command->flags.redir_l++;
		if (command->flags.redir_l > 1)
		{
			write(2, "Error: syntax error after unexpected token <\n", 45);
			command->shell->code = 1;
			command->flags.redir_l = 1;
		}
		return (1);
	}
	return (0);
}

static int	ft_redirect_r(int *i, char *line, t_command *command)
{
	if (line[*i] == '>')
	{
		(*i)++;
		command->flags.redir_r++;
		if (command->flags.redir_r > 1)
		{
			write(2, "Error: syntax error after unexpected token >\n", 45);
			command->shell->code = 1;
			command->flags.redir_r = 1;
		}
		if (line[*i] == '>')
		{
			(*i)++;
			(command->flags.redir_r)++;
		}
		command->type = command->type | REDIRECT;
		return (1);
	}
	return (0);
}

int			ft_if_redirect(int *i, char *line, t_command *command)
{
	if (ft_redirect_r(i, line, command) ||
			ft_redirect_l(i, line, command))
		return (1);
	return (0);
}
