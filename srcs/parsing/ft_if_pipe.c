/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:25:38 by ashea             #+#    #+#             */
/*   Updated: 2021/01/22 13:39:13 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	ft_syntax_error_pipe(int *i, char *line,
		t_command **command, t_shell *shell)
{
	if (!((*command)->list))
	{
		write(2, "Error: syntax error near unexpected token |\n", 44);
		shell->code = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

int			ft_if_pipe(int *i, char *line, t_command **command, t_shell *shell)
{
	int		fd_p[2];

	if (line[*i] == '|')
	{
		if (ft_syntax_error_pipe(i, line, command, shell))
			return (1);
		pipe(fd_p);
		if ((*command)->type == DEFAULT)
			(*command)->output = fd_p[1];
		(*command)->type = (*command)->type | PIPE;
		(*command)->execute(*command);
		if ((*command)->type & REDIRECT == REDIRECT)
			close(fd_p[1]);
		(*command)->destroy(*command);
		*command = new_command(shell, fd_p[0], 1);
		(*command)->type = (*command)->type | PIPE;
		(*i)++;
		return (1);
	}
	return (0);
}
