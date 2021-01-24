/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:25:38 by ashea             #+#    #+#             */
/*   Updated: 2021/01/24 16:57:27 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	ft_syntax_error_pipe(int *i, t_command *command)
{
	if (!(command->list))
	{
		write(2, "Error: syntax error near unexpected token |\n", 44);
		command->shell->code = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

int			ft_if_pipe(int *i, char *line, t_command **command)
{
	int		fd_p[2];
	t_shell *shell;

	if (line[*i] == '|')
	{
		if (ft_syntax_error_pipe(i, *command))
			return (1);
		pipe(fd_p);
		if (((*command)->type & REDIRECT) == REDIRECT)
			close(fd_p[1]);
		else
			(*command)->output = fd_p[1];
		(*command)->type = (*command)->type | PIPE;
		(*command)->execute(*command);
		shell = (*command)->shell;
		(*command)->destroy(*command);
		*command = new_command(shell, fd_p[0], 1);
		(*command)->type = (*command)->type | PIPE;
		(*i)++;
		return (1);
	}
	return (0);
}
