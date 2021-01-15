/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:05:21 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/15 20:57:29 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../includes/t_command.h"
#include "../includes/t_shell.h"
#include "../includes/t_buildin.h"
#include "../includes/buildins.h"
#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/utils.h"
#include "../includes/t_env.h"

int print_name()
{
    write(1, "\e[1;34mminishell\e[0m$> ", 23);
    return (0);
}

void putnlandname()
{
    write(1, "\n", 1);
    print_name();
}

void del()
{
    write(1, "\b \b", 3);
    write(1, "\b \b", 3);
}

static int start(t_shell *shell)
{
    char *line;
    line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    int r;

    while (1)
    {
        signal(SIGINT, putnlandname);
        signal(SIGQUIT, del);
        print_name();
        while (!(r = get_next_line(0, &line)) && ft_strlen(line))
                ;
        if (r < 0)
            break;
        if ((r == 0 && ft_strlen(line) == 0) || !ft_strncmp(line, "exit", 4))
        {   
            write(1, "exit\n", 5);
            break;
        }
        ft_parsing(shell, line);
        free(line);
        
    }
    free(line);
    return (0);
}

static void destroy(t_shell *shell)
{
    if (!shell)
        return;
    shell->env->destroy(shell->env);
    ft_bzero(shell, sizeof(t_shell));
    free(shell);
}

static int constructor(t_shell *shell, char **env)
{
    shell->destroy = destroy;
    shell->in = dup(0);
    shell->out = dup(1);
    shell->start = start;
    if (!(shell->env = new_env(env)))
        return (-1);
    return (0);
}

t_shell *new_shell(char **env)
{
    t_shell *shell;

    if (!(shell = malloc(sizeof(t_shell))))
        return (NULL);
    if (constructor(shell, env) < 0)
    {
        destroy(shell);
        return NULL;
    }
    return shell;
}
