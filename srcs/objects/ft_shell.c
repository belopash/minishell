/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:05:21 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 19:39:14 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../includes/t_command.h"
#include "../includes/t_shell.h"
#include "../includes/t_builtin.h"
#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/utils.h"
#include "../includes/t_env.h"

static int	start(t_shell *shell)
{
	char	*line;
	int		r;

	while (1)
	{
		signal(SIGINT, putnlandname);
		signal(SIGQUIT, delete);
		print_name();
		while (!(r = get_next_line(0, &line)) && ft_strlen(line))
			;
		if (r < 0)
			break ;
		if ((r == 0 && ft_strlen(line) == 0))
		{
			write(1, "exit\n", 5);
			exit(shell->code);
		}
		ft_parsing(shell, line);
		free(line);
	}
	free(line);
	return (0);
}

static void	destroy(t_shell *shell)
{
	if (!shell)
		return ;
	close(shell->in);
	close(shell->out);
	shell->env->destroy(shell->env);
	ft_bzero(shell, sizeof(t_shell));
	free(shell);
}

static void	constructor(t_shell *shell, char **env, t_builtin *builtins)
{
	shell->destroy = destroy;
	shell->in = dup(0);
	shell->out = dup(1);
	shell->start = start;
	shell->code = 0;
	if (!(shell->env = new_env(env)))
		exit(1);
	if (!(shell->builtins = new_builtins(shell, builtins)))
		exit(1);
}

t_shell		*new_shell(char **env, t_builtin *builtins)
{
	t_shell *shell;

	if (!(shell = malloc(sizeof(t_shell))))
		exit(1);
	constructor(shell, env, builtins);
	return (shell);
}
