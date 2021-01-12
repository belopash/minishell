/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:16:09 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/12 12:15:32 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>
#include "../includes/t_command.h"
#include <sys/types.h>
#include "../includes/buildins.h"
#include "../includes/utils.h"
#include "../includes/libft.h"
#include "../includes/t_shell.h"

int execute(t_shell *shell, t_command command)
{
    int ret;
    struct stat sb;

    char **args = ft_toarray(command.list);
    if (!fork())
    {
        dup2(command.input, 0);
        dup2(command.output, 1);
        if (command.input != 0)
            close(command.input);
        if (command.output != 1)
            close(command.output);

        if (execbi(shell, args) == 0)
            exit(0);

        char **paths = ft_split(shell->getenv(shell, "PATH"), ':');
        int i = 0;

        char *path = args[0];
        while (!(stat((const char *)path, &sb) == 0 && (sb.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))))
		{
            if (!paths[i])
                exit(-1);
            path = ft_pathjoin(paths[i], args[0]);
            i++;
		}

		return execve(path, args, ft_toarray(shell->env));
    }
    if (command.input != 0)
        close(command.input);
    if (command.output != 1)
        close(command.output);
    free(args);
}