/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newShell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:05:21 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/12 12:17:27 by bbrock           ###   ########.fr       */
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

char **ft_create_array(t_list *list)
{
    int i;
    char **argv;
    i = 0;
    argv = (char **)malloc(sizeof(char *) * (ft_lstsize(list) + 1));
    while (list)
    {
        argv[i] = list->content;
        list = list->next;
        i++;
    }
    argv[i] = NULL;
    return (argv);
}

void ft_lst_print(t_list *list)
{
    while (list)
    {
        ft_putendl_fd(list->content, 1);
        list = list->next;
    }
}

char *ft_together(t_list *list)
{
    char *var = "";
    while (list)
    {
        var = ft_strjoin(var, list->content);
        var = ft_strjoin(var, " ");
        list = list->next;
    }
    return (var);
}

char *ft_search_env(int *i, char *line, char **env)
{
    char *var;
    int j;

    var = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
    j = 0;
    while (line[*i] != ' ' && line[*i] != '$' && line[*i] != '"' && line[*i] != '\'' && line[*i] != ';' && line[*i])
    {
        var[j] = line[*i];
        j++;
        (*i)++;
    }
    int k = 0;

    while (env[k])
    {
        if (!ft_strncmp(env[k], var, j))
        {
            if (env[k][j] == '=')
                return (ft_strdup(env[k] + j + 1));
        }
        k++;
    }
    return (ft_strdup(""));
}

void ft_exit()
{
    write(1, "\n", 1);
}

void ft_add_arg(int *j, char **content, int *flag_right_redirect, int *flag_left_redirect, t_command *command)
{
    (*content)[*j] = '\0';
    *j = 0;

    if (*flag_right_redirect == 0 && *flag_left_redirect == 0)
    {
        ft_lstadd_back(&(command->list), ft_lstnew(ft_strdup(*content)));
    }
    else
    {
        if (*flag_right_redirect != 0)
        {
            if (*flag_right_redirect == 1)
                command->output = open(*content, O_CREAT | O_WRONLY | O_TRUNC, 0666);
            else
                command->output = open(*content, O_CREAT | O_WRONLY | O_APPEND, 0666);
            *flag_right_redirect = 0;
        }
        if (*flag_left_redirect != 0)
        {
            command->input = open(*content, O_CREAT | O_RDONLY, 0666);
            *flag_left_redirect = 0;
        }
    }
}
int print_name()
{
    write(1, "\e[1;34mminishell\e[0m$> ", 23);
}

void putnlandname()
{
    write(1, "\n", 1);
    print_name();
}

void putnl()
{
}
int ft_parsing(t_shell *shell, char *line)
{
    char *content;
    int i;
    int j;

    content = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
    i = 0;
    j = 0;
    t_command command = (t_command){0, 1, NULL};
    
    signal(SIGINT, putnl);

    int flag_right_redirect = 0;
    int flag_left_redirect = 0;
    while (!i || line[i - 1])
    {

        if (line[i] == ';' || line[i] == '\0')
        {
            if (j > 0)
                ft_add_arg(&j, &content, &flag_right_redirect, &flag_left_redirect, &command);

            int pid;
            int status;
            execute(shell, command);

            while ((pid = wait(&status)) > 0)
                ;
            command = (t_command){0, 1, NULL};
            i++;
            continue;
        }

        if (line[i] == '|')
        {
            if (j > 0)
                ft_add_arg(&j, &content, &flag_right_redirect, &flag_left_redirect, &command);
            // ft_putendl_fd(ft_together(command.list), 1);

            int fd_p[2];
            pipe(fd_p);
            if (command.output == 1)
                command.output = fd_p[1];
            else
                dup2(command.output, fd_p[0]);
            execute(shell, command);
            command = (t_command){fd_p[0], 1, NULL};

            i++;
            continue;
        }

        if (line[i] == '>')
        {
            if (j > 0)
                ft_add_arg(&j, &content, &flag_right_redirect, &flag_left_redirect, &command);
            flag_right_redirect++;
            i++;
            continue;
        }

        if (line[i] == '<')
        {
            if (j > 0)
                ft_add_arg(&j, &content, &flag_right_redirect, &flag_left_redirect, &command);
            flag_left_redirect = 1;
            i++;
            continue;
        }

        if (line[i] == '$' && line[i + 1] != '\\' && line[i + 1] != ' ' && line[i + 1] != '\'' && line[i + 1] != '"' && line[i + 1] != '\0')
        {
            i++;
            char *tmp;
            tmp = ft_search_env(&i, line, ft_toarray(shell->env));

            while (tmp[0])
            {
                content[j] = tmp[0];
                tmp++;
                j++;
            }

            if (line[i] == ' ' || line[i] == '\0')
            {
                if (j > 0)
                    ft_add_arg(&j, &content, &flag_right_redirect, &flag_left_redirect, &command);
            }
            continue;
        }

        if (line[i] == '"')
        {
            i++;
            while (line[i] != '"' && line[i])
            {
                if (line[i] == '$' && line[i + 1] != '\\' && line[i + 1] != ' ' && line[i + 1] != '\'' && line[i + 1] != '"' && line[i + 1] != '\0')
                {
                    i++;
                    char *tmp;
                    tmp = ft_search_env(&i, line, ft_toarray(shell->env));
                    while (tmp[0])
                    {
                        content[j] = tmp[0];
                        tmp++;
                        j++;
                    }
                    continue;
                }
                if (line[i] == '\\' && (line[i + 1] == 'n'))
                {
                    i += 2;
                    content[j] = '\n';
                    j++;
                    continue;
                }
                if (line[i] == '\\' && (line[i + 1] == '\\' || line[i + 1] == '\'' || line[i + 1] == '"' || line[i + 1] == '$'))
                    i++;

                content[j] = line[i];
                j++;
                i++;
            }
            if (line[i] == '"')
                i++;
            if (line[i] == ' ' || line[i] == '\0')
            {
                if (j > 0)
                    ft_add_arg(&j, &content, &flag_right_redirect, &flag_left_redirect, &command);
            }
            continue;
        }

        if (line[i] == '\'')
        {
            i++;
            while (line[i] != '\'' && line[i])
            {
                if (line[i] == '\\' && (line[i + 1] == 'n'))
                {
                    i += 2;
                    content[j] = '\n';
                    j++;
                    continue;
                }
                if (line[i] == '\\' && (line[i + 1] == '\\'))
                    i++;
                content[j] = line[i];
                j++;
                i++;
            }
            if (line[i] == '\'')
                i++;
            if (line[i] == ' ' || line[i] == '\0')
            {
                if (j > 0)
                    ft_add_arg(&j, &content, &flag_right_redirect, &flag_left_redirect, &command);
            }
            continue;
        }

        if (line[i] == ' ')
        {
            i++;
            continue;
        }

        if (line[i] == '\\')
            i++;

        content[j] = line[i];
        j++;
        i++;
        if (line[i] == ' ' || line[i] == '\0')
        {
            if (j > 0)
                ft_add_arg(&j, &content, &flag_right_redirect, &flag_left_redirect, &command);
        }
    }
    return (0);
}


char *ft_getenv(t_shell *shell, char *name)
{
    t_list *item;

	item = shell->env;
	while (item)
	{
		if (ft_strncmp(item->content, name, ft_strlen(name)) == 0)
            return (item->content + ft_strlen(name) + 1);
		item = item->next;
	}
    return (NULL);
}

int start(t_shell *shell)
{
    char *line;
    line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));

    while (1)
    {
        signal(SIGINT, putnlandname);
        print_name();
        int r = get_next_line(0, &line);
        if (!ft_strlen(line) && r > 0)
            continue;
        if (!ft_strncmp(line, "exit", 4) || r <= 0)
        {
            write(1, "exit\n", 5);
            break;
        }
        ft_parsing(shell, line);
    }
    free(line);
    return (0);
}

t_shell *newShell(char **env)
{
    t_shell *shell;

    if (!(shell = malloc(sizeof(t_shell))))
        return (NULL);
    if (!(shell->env = ft_tolist(env)))
		return (NULL);
    shell->in = dup(0);
    shell->out = dup(1);
    shell->start = start;
    shell->getenv = ft_getenv;
}