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
#include "../includes/t_builtin.h"
#include "../includes/builtins.h"
#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/utils.h"
#include <limits.h>
#ifndef PATH_MAX
#include <linux/limits.h>
#endif

static void ft_lst_print(t_list *list)
{
    while (list)
    {
        ft_putendl_fd(list->content, 1);
        list = list->next;
    }
}

static char *ft_together(t_list *list)
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

static char *ft_search_env(int *i, char *line, char **env)
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

static void ft_add_arg(int *j, char **content, t_command *command)
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

static void putnl()
{
}

static int ft_if_env(int *j, char *content, char *line, t_shell *shell)
{
    int i;
    i = 0;

    if (line[i] == '$' && ((line[i + 1] != '\\' && line[i + 1] != ' ' && line[i + 1] != '\'' && line[i + 1] != '"' && line[i + 1] != '\0') || line[i + 1] == '?'))
    {
        i++;
        char *tmp;
        if (line[i] == '?')
        {
            i++;
            tmp = ft_strdup(ft_itoa(shell->code));
        }
        else
            tmp = ft_search_env(&i, line, ft_toarray(shell->env->list));
        while (tmp[0])
        {
            content[*j] = tmp[0];
            tmp++;
            (*j)++;
        }
    }
    return (i);
}

static int ft_if_double_quotes(int *j, char *content, char *line, t_shell *shell)
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
            while (line[i] != '\0' && line[i] != '"' && line[i] != '$')
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
    return (i);
}

static int ft_if_single_quotes(int *j, char *content, char *line, t_shell *shell)
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
    return (i);
}

static int if_next_command(int *i, char *line, t_command **command, t_shell *shell)
{
    int exit = 0;

    if (line[*i] == ';' || line[*i] == '\0')
    {
        int pid;
        int status;
        (*command)->execute(*command);
        while ((pid = wait(&status)) > 0)
        {
            if (WIFEXITED(status))
            {
                if ((shell->code = WEXITSTATUS(status)) != 0)
                {
                    kill(0, SIGQUIT);
                    exit = 1;
                }
            }
            else if (WIFSIGNALED(status))
            {
                if (!exit)
                    write(1, "\n", 1);
                kill(0, SIGQUIT);
                exit = 1;
            }
        }
        (*command)->destroy(*command);
        *command = new_command(shell, 0, 1);
        (*i)++;
        return (1);
    }
    return (0);
}

static int ft_if_pipe(int *i, char *line, t_command **command, t_shell *shell)
{
    if (line[*i] == '|')
    {
        int fd_p[2];
        pipe(fd_p);
        if ((*command)->type == DEFAULT)
            (*command)->output = fd_p[1];
        (*command)->type = (*command)->type | PIPE;
        if ((*command)->type == REDPIPE)
        {
            int fd = open(((*command)->filename), O_RDONLY, 0666);
            dup2(fd, fd_p[0]);
        }
        (*command)->execute((*command));
        (*command)->destroy(*command);
        *command = new_command(shell, fd_p[0], 1);
        (*command)->type = (*command)->type | PIPE;
        (*i)++;
        return (1);
    }
    return (0);
}

static int ft_if_redirect(int *i, char *line, t_command *command)
{
    if (line[*i] == '>')
    {
        (command->flags.redir_r)++;
        command->type = command->type | REDIRECT;
        (*i)++;
        return (1);
    }
    if (line[*i] == '<')
    {
        command->flags.redir_l = 1;
        (*i)++;
        return (1);
    }
    return (0);
}

int ft_parsing(t_shell *shell, char *line)
{
    char *content;
    int i;
    int j;

    content = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
    i = 0;
    j = 0;
    t_command *command = new_command(shell, 0, 1);
    signal(SIGINT, putnl);
    signal(SIGQUIT, putnl);
    if (line[0] == '\0')
        return (0);
    while (!i || line[i - 1])
    {
        if ((line[i] == ' ' || line[i] == '\0' || line[i] == ';' || line[i] == '|' || line[i] == '>' || line[i] == '<') && (j > 0))
            ft_add_arg(&j, &content, command);
        if (if_next_command(&i, line, &command, shell))
            continue;
        if (ft_if_pipe(&i, line, &command, shell))
            continue;
        if (ft_if_redirect(&i, line, command))
            continue;
        if (line[i] == ' ')
        {
            i++;
            continue;
        }

        if (i < (i = i + ft_if_env(&j, content, line + i, shell)))
            continue;
        if (i < (i = i + ft_if_double_quotes(&j, content, line + i, shell)))
            continue;
        if (i < (i = i + ft_if_single_quotes(&j, content, line + i, shell)))
            continue;
        if (line[i] == '\\')
            i++;
        while (line[i] != ' ' && line[i] != '\0' && line[i] != '\'' && line[i] != '"' && line[i] != '$' && line[i] != ';' && line[i] != '|' && line[i] != '>' && line[i] != '<')
        {
            content[j] = line[i];
            j++;
            i++;
        }
    }
    return (0);
}
