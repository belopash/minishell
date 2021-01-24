/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:59:07 by ashea             #+#    #+#             */
/*   Updated: 2021/01/22 16:07:48 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void		ft_add_arg(int *j, char *content, t_command *command)
{
	content[*j] = '\0';
	*j = 0;
	if (command->flags.redir_r == 0 && command->flags.redir_l == 0)
		ft_lstadd_back(&(command->list), ft_lstnew(ft_strdup(content)));
	else
	{
		if (command->flags.redir_r != 0)
		{
			if (command->flags.redir_r == 1)
				command->output = open(content,
										O_CREAT | O_WRONLY | O_TRUNC, 0666);
			else
				command->output = open(content,
										O_CREAT | O_WRONLY | O_APPEND, 0666);
			command->flags.redir_r = 0;
		}
		if (command->flags.redir_l != 0)
		{
			command->input = open(content, O_RDONLY, 0666);
			command->flags.redir_l = 0;
		}
		if (command->output < 0 || command->input < 0)
			error(content, strerror(errno), 1);
		command->filename = content;
	}
}
