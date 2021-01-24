/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:20:06 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/24 16:31:58 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "../../includes/t_command.h"
#include "../../includes/t_builtin.h"
#include "../../includes/utils.h"
#include "../../includes/libft.h"
#include "../../includes/t_shell.h"

static int	execbi(t_command *command, char **args)
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

static char	*find_path(char *pathv, char *name)
{
	char		**paths;
	char		*path;
	struct stat	sb;
	int			i;

	i = 0;
	if (!(paths = ft_split(pathv, ':')))
		return (name);
	while (paths[i])
	{
		path = ft_pathjoin(paths[i], name);
		if ((stat((const char *)path, &sb) == 0))
			break ;
		if (path)
			free(path);
		if (!paths[i + 1])
			path = name;
		i++;
	}
	ft_free2(paths);
	return (path);
}

static void	start_process(t_command *command, char **args)
{
	char *prog;
	char **envs;

	if (!fork())
	{
		prog = find_path(command->shell->env->get(command->shell->env, "PATH"),
							args[0]);
		envs = ft_toarray(command->shell->env->list);
		execve(prog, args, envs);
		exit(error(args[0], strerror(errno), 1));
	}
}

int			execute(t_command *command)
{
	char **args;

	dup2(command->input, 0);
	dup2(command->output, 1);
	if (command->input != 0 && command->input > 0)
		close(command->input);
	if (command->output != 1 && command->output > 0)
		close(command->output);
	if (command->list && command->input >= 0 && command->output >= 0)
	{
		if (command->input != 0 && command->input > 0)
			close(command->input);
		if (command->output != 1 && command->output > 0)
			close(command->output);
		args = ft_toarray(command->list);
		if (execbi(command, args) < 0)
			start_process(command, args);
		free(args);
	}
	if (command->input != 0 && command->input > 0)
		dup2(command->shell->in, 0);
	if (command->output != 1 && command->output > 0)
		dup2(command->shell->out, 1);
	return (0);
}
