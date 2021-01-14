/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newShell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:05:21 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/14 18:41:40 by bbrock           ###   ########.fr       */
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

void ft_add_arg(int *j, char **content, t_command *command)
{
    (*content)[*j] = '\0';
    *j = 0;

    if (command->flags.redir_r == 0 && command->flags.redir_l == 0)
    {
        ft_lstadd_back(&(command->list), ft_lstnew(ft_strdup(*content)));
    }
    else
    {
        if (command->flags.redir_r != 0)
        {
            if (command->flags.redir_r == 1)
                command->output = open(*content, O_CREAT | O_WRONLY | O_TRUNC, 0666);
            else
                command->output = open(*content, O_CREAT | O_WRONLY | O_APPEND, 0666);
            command->flags.redir_r = 0;
        }
        if (command->flags.redir_l != 0)
        {
            command->input = open(*content, O_CREAT | O_RDONLY, 0666);
            command->flags.redir_l = 0;
        }
        command->filename = *content;
    }
}
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

void putnl()
{
}

int ft_if_env(int *j, char *content, char *line, t_shell *shell)
{
    int i;
    i = 0;
    if (line[i] == '$' && line[i + 1] != '\\' && line[i + 1] != ' ' && line[i + 1] != '\'' && line[i + 1] != '"' && line[i + 1] != '\0')
           {
               i++;
               char *tmp;
               tmp = ft_search_env(&i, line, ft_toarray(shell->env));
               while (tmp[0])
               {
                   content[*j] = tmp[0];
                   tmp++;
                   (*j)++;
               }
           }
    return(i);
}

int ft_if_double_quotes(int *j, char *content, char *line, t_shell *shell)
{
    int i;
    i = 0;
    if (line[i] == '"')
    {
        i++;
        while (line[i] != '"' && line[i])
        {
            i += ft_if_env(j, content, line + i, shell);
            if (line[i] == '\\' && (line[i + 1] == '\\' || line[i + 1] == '\'' || line[i + 1] == '"' || line[i + 1] == '$'))
                i++;
            while (line[i] != '\0' && line[i] != '\'' && line[i] != '"' && line[i] != '$')
            {
                if (line[i] == '\\' && (line[i + 1] == 'n'))
                {
                    content[*j] = '\n';
                    (*j)++;
                    i += 2;
                    continue;
                }
                content[*j] = line[i];
                (*j)++;
                i++;
            }
        }
        i++;
    }
    return(i);
}

int ft_if_single_quotes(int *j, char *content, char *line, t_shell *shell)
{
    int i;
    i = 0;
    
    if (line[i] == '\'')
    {
        i++;
        while (line[i] != '\'' && line[i])
        {
            if (line[i] == '\\' && (line[i + 1] == 'n'))
            {
                i += 2;
                content[*j] = '\n';
                (*j)++;
                continue;
            }
            if (line[i] == '\\' && (line[i + 1] == '\\'))
                i++;
            content[*j] = line[i];
            (*j)++;
            i++;
        }
        i++;
    }
    return(i);
}

int if_next_command(int *i, char *line, t_command *command, t_shell *shell)
{
    if (line[*i] == ';' || line[*i] == '\0')
    {
        int pid;
        int status;
        execute(shell, *command);
        while ((pid = wait(&status)) > 0)
            ;
        *command = (t_command){0, 1, NULL, 0, 0, {0, 0}};
        (*i)++;
        return (1);
    }
    return (0);
}

int ft_if_pipe(int *i, char *line, t_command *command, t_shell *shell)
{
    if (line[*i] == '|')
    {
        int fd_p[2];
        pipe(fd_p);
        if (command->type == DEFAULT)
            command->output = fd_p[1];
        command->type = command->type | PIPE;
        if (command->type == REDPIPE)
        {
            int fd = open((command->filename), O_RDONLY, 0666);
            dup2(fd, fd_p[0]);
        }
        execute(shell, *command);
        *command = (t_command){fd_p[0], 1, NULL, 0, 0, {0, 0}};
        (*i)++;
        return (1);
    }
    return (0);
}

int ft_if_redirect(int *i, char *line, t_command *command)
{
    if (line[*i] == '>')
    {
        (command->flags.redir_r)++;
        command->type = command->type | REDIRECT;
        (*i)++;
        return(1);
    }
    if (line[*i] == '<')
    {
        command->flags.redir_l = 1;
        (*i)++;
        return(1);
    }
    return(0);
}

int ft_parsing(t_shell *shell, char *line)
{
    char *content;
    int i;
    int j;

    content = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
    i = 0;
    j = 0;
    t_command command = (t_command){0, 1, NULL, 0, 0, {0, 0}};
    signal(SIGINT, putnl);
    while (!i || line[i - 1])
    {
        if ((line[i] == ' ' || line[i] == '\0' || line[i] == ';' || line[i] == '|' || line[i] == '>' || line[i] == '<') && (j > 0))
            ft_add_arg(&j, &content, &command);
        if (if_next_command(&i, line, &command, shell))
            continue;
        if (ft_if_pipe(&i, line, &command, shell))
            continue;
        if (ft_if_redirect(&i, line, &command))
            continue;
        if (line[i] == ' ')
        {
            i++;
            continue;
        }
        i += ft_if_env(&j, content, line + i, shell);
        i += ft_if_double_quotes(&j, content, line + i, shell);
        i += ft_if_single_quotes(&j, content, line + i, shell);
        if (line[i] == '\\')
            i++;
        while (line[i] != ' ' && line[i] != '\0' && line[i] != '\'' && line[i] != '"' && line[i] != '$' && line[i] != ';')
        {
            content[j] = line[i];
            j++;
            i++;
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
    return shell;
}
