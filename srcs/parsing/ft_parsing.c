/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:18:01 by ashea             #+#    #+#             */
/*   Updated: 2021/01/26 17:12:34 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int		ft_parsing_arg(int *j, char *content, char *line,
		t_command *command)
{
	int			delta;

	delta = 0;
	if ((delta = ft_if_env(j, content, line, command)) > 0)
		return (delta);
	if ((delta = ft_if_double_quotes(j, content, line, command)) > 0)
		return (delta);
	if ((delta = ft_if_single_quotes(j, content, line, command)) > 0)
		return (delta);
	if ((delta = ft_if_other_char(j, content, line)) > 0)
		return (delta);
	return (0);
}

static int		ft_parsing_special_character(int *i, char *line,
		t_command **command)
{
	if (ft_if_next_command(i, line, command))
		return (1);
	if (ft_if_pipe(i, line, command))
		return (1);
	if (ft_if_redirect(i, line, *command))
		return (1);
	return (0);
}

static void		ft_parsing_dop(char *content, char *line, t_command **command)
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
			ft_add_arg(&j, content, *command);
		if (ft_parsing_special_character(&i, line, command))
			continue;
		if ((delta = ft_parsing_arg(&j, content, line + i, *command)) > 0)
		{
			i += delta;
			continue;
		}
	}
}

static void		donothing(int i)
{
	(void)i;
}

int				ft_parsing(t_shell *shell, char *line)
{
	char		*content;
	t_command	*command;

	if (!(content = (char *)ft_calloc((ft_strlen(line) * PATH_MAX + 1),
					sizeof(char))))
		exit(-1);
	command = new_command(shell, 0, 1);
	signal(SIGINT, donothing);
	signal(SIGQUIT, donothing);
	if (line[0] != '\0')
		ft_parsing_dop(content, line, &command);
	free(content);
	command->destroy(command);
	return (0);
}
