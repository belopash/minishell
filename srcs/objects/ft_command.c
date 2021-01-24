/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:16:09 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/24 16:31:32 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/t_command.h"
#include "../includes/t_builtin.h"
#include "../includes/libft.h"
#include "../includes/t_shell.h"

static void	destroy(t_command *command)
{
	if (!command)
		return ;
	ft_lstclear(&(command->list), free);
	ft_bzero(command, sizeof(t_command));
	if (command->input != 0 && command->input > 0)
		close(command->input);
	if (command->output != 1 && command->output > 0)
		close(command->output);
	free(command);
}

static void	constructor(t_command *command,
						t_shell *shell, int input, int output)
{
	command->type = DEFAULT;
	command->output = output;
	command->input = input;
	command->list = NULL;
	command->flags.redir_l = 0;
	command->flags.redir_r = 0;
	command->shell = shell;
	command->execute = execute;
	command->destroy = destroy;
}

t_command	*new_command(t_shell *shell, int input, int output)
{
	t_command *command;

	if (!(command = malloc(sizeof(t_command))))
		exit(1);
	constructor(command, shell, input, output);
	return (command);
}
