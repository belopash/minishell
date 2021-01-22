/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:18:01 by ashea             #+#    #+#             */
/*   Updated: 2021/01/22 13:24:22 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int		ft_parsing_arg(int *j, char *content, char *line,
		t_shell *shell)
{
	int			delta;

	delta = 0;
	if ((delta = ft_if_env(j, content, line, shell)) > 0)
		return (delta);
	if ((delta = ft_if_double_quotes(j, content, line, shell)) > 0)
		return (delta);
	if ((delta = ft_if_single_quotes(j, content, line, shell)) > 0)
		return (delta);
	if ((delta = ft_if_other_char(j, content, line, shell)) > 0)
		return (delta);
	return (0);
}

static int		ft_parsing_special_character(int *i, char *line,
		t_command **command, t_shell *shell)
{
	if (ft_if_next_command(i, line, command, shell))
		return (1);
	if (ft_if_pipe(i, line, command, shell))
		return (1);
	if (ft_if_redirect(i, line, *command, shell))
		return (1);
	return (0);
}

static void		ft_parsing_dop(char *content, char *line,
		t_command **command, t_shell *shell)
{
	int			i;
	int			j;
	int			delta;

	i = 0;
	j = 0;
	while (!i || line[i - 1])
	{
		if ((line[i] == ' ' || line[i] == '\0' ||
					line[i] == ';' || line[i] == '|' ||
					line[i] == '>' || line[i] == '<') && (j > 0))
			ft_add_arg(&j, &content, *command);
		if (ft_parsing_special_character(&i, line, command, shell))
			continue;
		if ((delta = ft_parsing_arg(&j, content, line + i, shell)) > 0)
		{
			i += delta;
			continue;
		}
	}
}

static void		putnl(void)
{
}

int				ft_parsing(t_shell *shell, char *line)
{
	char		*content;
	t_command	*command;

	if (!(content = (char *)malloc(sizeof(char) * (PATH_MAX + 1))))
		exit(-1);
	command = new_command(shell, 0, 1);
	signal(SIGINT, putnl);
	signal(SIGQUIT, putnl);
	if (line[0] == '\0')
		return (0);
	ft_parsing_dop(content, line, &command, shell);
	return (0);
}
