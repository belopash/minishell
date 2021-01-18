/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:16:09 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/18 12:52:51 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>
#include "../includes/t_command.h"
#include <sys/types.h>
#include "../includes/t_buildin.h"
#include "../includes/utils.h"
#include "../includes/libft.h"
#include "../includes/t_shell.h"

int execute(t_command *command)
{
    int ret;
    struct stat sb;

    char **args = ft_toarray(command->list);

    if (command->input != 0)
    {
        dup2(command->input, 0);
        close(command->input);
    }
    if (command->output != 1)
    {
        dup2(command->output, 1);
        close(command->output);
    }
    if (find_buildin(args[0]))
    {
        if (command->type & PIPE == PIPE)
        {
            if (!fork())
                exit(execbi(command->shell, args));
        }
        else
        {
            execbi(command->shell, args);
        }
        if (command->input != 0)
            dup2(command->shell->in, 0);
        if (command->input != 1)
            dup2(command->shell->out, 1);
    }
    else
    {
        if (!fork())
        {
            char **paths = ft_split(command->shell->env->get(command->shell->env, "PATH"), ':');
            int i = 0;

            char *path = args[0];
            while (!(stat((const char *)path, &sb) == 0 && (sb.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))))
            {
                if (!paths[i])
                    exit(-1);
                path = ft_pathjoin(paths[i], args[0]);
                i++;
            }
            return execve(path, args, ft_toarray(command->shell->env->list));
        }
    }
    free(args);
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
        return (NULL);
    if (constructor(command, shell, input, output) < 0)
    {
        destroy(command);
        return (NULL);
    }
    return command;
}
