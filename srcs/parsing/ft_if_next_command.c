/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_next_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:21:12 by ashea             #+#    #+#             */
/*   Updated: 2021/01/22 12:42:28 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static void		ft_next_command_ut(t_shell *shell)
{
    int pid;
    int status;
    int exit;
    
    exit = 0;
    while ((pid = wait(&status)) > 0)
    {
        if (exit)
            continue;
        if (WIFEXITED(status))
        {
            shell->code = WEXITSTATUS(status);
        }
        else if (WIFSIGNALED(status))
        {
            shell->code = WTERMSIG(status) + 128;
            write(1, "\n", 1);
            exit = 1;
        }
    }
}

static int		ft_syntax_error(int *i, char *line,
		t_command **command, t_shell *shell)
{
	if (line[*i] == ';' && !((*command)->list))
	{
		write(2, "Error: syntax error near unexpected token ;\n", 44);
		shell->code = 2;
		(*i)++;
		return (1);
	}
	if ((*command)->flags.redir_r > 0)
	{
		write(2, "Error: syntax error after unexpected token >\n", 45);
		shell->code = 2;
		(*command)->flags.redir_r = 0;
		return (1);
	}
	if ((*command)->flags.redir_l > 0)
	{
		write(2, "Error: syntax error after unexpected token <\n", 45);
		shell->code = 2;
		(*command)->flags.redir_l = 0;
		return (1);
	}
	return (0);
}

int				ft_if_next_command(int *i, char *line,
		t_command **command, t_shell *shell)
{
	if (line[*i] == ';' || line[*i] == '\0')
	{
		if (ft_syntax_error(i, line, command, shell))
			return (1);
		(*command)->execute(*command);
		ft_next_command_ut(shell);
		(*command)->destroy(*command);
		*command = new_command(shell, 0, 1);
		(*i)++;
		return (1);
	}
	return (0);
}
