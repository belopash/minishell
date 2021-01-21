/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:16:09 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/21 17:14:57 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>
#include "../includes/t_command.h"
#include <sys/types.h>
#include "../includes/t_builtin.h"
#include "../includes/utils.h"
#include "../includes/libft.h"
#include "../includes/t_shell.h"
#include <errno.h>

static int error(char *name, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
	return (1);
}

static int execbi(t_command *command, char **args)
{
	t_builtin *bi;

	bi = command->shell->builtins->get(command->shell->builtins, args[0]);
	if (!bi)
		return (-1);
	if ((command->type & PIPE) == PIPE)
	{
		if (!fork())
			exit(bi->command(bi, args));
	}
	else
		command->shell->code = bi->command(bi, args);
	return (0);
}

static char *find_path(char *PATH, char *name)
{
	char **paths;
	char *path;
	struct stat sb;
	int i;

	i = 0;
	paths = ft_split(PATH, ':');
	while (!(stat((const char *)path, &sb) == 0))
	{
		if (!paths[i])
		{
			path = name;
			break;
		}
		path = ft_pathjoin(paths[i], name);
		i++;
	}
	free(paths);
	return (path);
}

int execute(t_command *command)
{
	int ret;
	char **args;
	char *prog;

	dup2(command->input, 0);
	if (command->input != 0)
		close(command->input);
	dup2(command->output, 1);
	if (command->output != 1)
		close(command->output);
	if (command->list && command->input >= 0 && command->output >= 0)
	{
		args = ft_toarray(command->list);
		if (execbi(command, args) < 0)
		{
			if (!fork())
			{
				prog = find_path(command->shell->env->get(command->shell->env, "PATH"), args[0]);
				execve(prog, args, ft_toarray(command->shell->env->list));
				error(args[0], strerror(errno));
				exit(1);
			}
		}
		free(args);
	}
	if (command->input != 0)
		dup2(command->shell->in, 0);
	if (command->input != 1)
		dup2(command->shell->out, 1);
	return (0);
}

static void destroy(t_command *command)
{
	if (!command)
		return;
	ft_bzero(command, sizeof(t_command));
	free(command);
}

static int constructor(t_command *command, t_shell *shell, int input, int output)
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
	return (0);
}

t_command *new_command(t_shell *shell, int input, int output)
{
	t_command *command;

	if (!(command = malloc(sizeof(t_command))))
		exit(1);
	if (constructor(command, shell, input, output) < 0)
		exit(1);
	return command;
}
