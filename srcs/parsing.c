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
#include <errno.h>

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

static int error(char *name, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
	return (1);
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
			command->input = open(*content, O_RDONLY, 0666);
			command->flags.redir_l = 0;
		}
		if (command->output < 0 || command->input < 0)
			error(*content, strerror(errno));
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
		if (line[i] == '"' && (line[i + 1] == '\0' || line[i + 1] == ' ' || line[i + 1] == '>' || line[i + 1] == '<' || line[i + 1] == ';' || line[i + 1] == '|'))
		{
			content[*j] = '\0';
			(*j)++;
			i++;
			return (i);
		}
		while (line[i] != '"' && line[i])
		{
			if (i < (i = i + ft_if_env(j, content, line + i, shell)))
				continue;
			if (line[i] == '\\' && (line[i + 1] == '\\' || line[i + 1] == '$' || line[i + 1] == '"'))
				i++;
			content[*j] = line[i];
			(*j)++;
			i++;
		}
		if (line[i] == '\0')
		{
			write(2, "Error: quote not closed\n", 24);
			(*j) = 0;
			shell->code = 1;
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
		if (line[i] == '\'' && (line[i + 1] == '\0' || line[i + 1] == ' ' || line[i + 1] == '>' || line[i + 1] == '<' || line[i + 1] == ';' || line[i + 1] == '|'))
		{
			content[*j] = '\0';
			(*j)++;
			i++;
			return (i);
		}
		while (line[i] != '\'' && line[i])
		{
			content[*j] = line[i];
			(*j)++;
			i++;
		}
		if (line[i] == '\0')
		{
			write(2, "Error: quote not closed\n", 24);
			(*j) = 0;
			shell->code = 1;
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
		if (line[*i] == ';' && !((*command)->list))
		{
			write(2, "Error: syntax error near unexpected token ;\n", 44);
			shell->code = 2;
			(*i)++;
			return (1);
		}

		if ((*command)->flags.redir_r > 0)
		{
			write(2, "Error: syntax error after unexpected token >\n", 45);
			shell->code = 2;
			(*command)->flags.redir_r = 0;
			return (1);
		}

		if ((*command)->flags.redir_l > 0)
		{
			write(2, "Error: syntax error after unexpected token <\n", 45);
			shell->code = 2;
			(*command)->flags.redir_l = 0;
			return (1);
		}

		int pid;
		int status;
		(*command)->execute(*command);
		while ((pid = wait(&status)) > 0)
		{
			if (exit)
				continue;
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
				shell->code = WTERMSIG(status) + 128;
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
		if (!((*command)->list))
		{
			write(2, "Error: syntax error near unexpected token |\n", 44);
			shell->code = 1;
			(*i)++;
			return (1);
		}

		int fd_p[2];
		pipe(fd_p);
		if ((*command)->type == DEFAULT)
			(*command)->output = fd_p[1];
		(*command)->type = (*command)->type | PIPE;
		(*command)->execute(*command);
		if ((*command)->type & REDIRECT == REDIRECT)
			close(fd_p[1]);
		(*command)->destroy(*command);
		*command = new_command(shell, fd_p[0], 1);
		(*command)->type = (*command)->type | PIPE;
		(*i)++;
		return (1);
	}
	return (0);
}

static int ft_if_redirect(int *i, char *line, t_command *command, t_shell *shell)
{
	if (line[*i] == '>')
	{
		(*i)++;
		(command->flags.redir_r)++;
		if (command->flags.redir_r > 1)
		{
			write(2, "Error: syntax error after unexpected token >\n", 45);
			shell->code = 1;
			command->flags.redir_r = 1;
		}
		if (line[*i] == '>')
		{
			(*i)++;
			(command->flags.redir_r)++;
		}
		command->type = command->type | REDIRECT;
		return (1);
	}
	if (line[*i] == '<')
	{
		(*i)++;
		command->flags.redir_l++;
		if (command->flags.redir_l > 1)
		{
			write(2, "Error: syntax error after unexpected token <\n", 45);
			shell->code = 1;
			command->flags.redir_l = 1;
		}
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
		if (ft_if_redirect(&i, line, command, shell))
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
		{
			i++;
			if (line[i] == '\'' || line[i] == '"' || line[i] == '$' || line[i] == ';' || line[i] != '|' || line[i] != '>' || line[i] != '<')
			{
				content[j] = line[i];
				j++;
				i++;
			}
			continue;
		}
		while (line[i] != ' ' && line[i] != '\0' && line[i] != '\'' && line[i] != '"' && line[i] != '$' && line[i] != ';' && line[i] != '|' && line[i] != '>' && line[i] != '<')
		{
			content[j] = line[i];
			j++;
			i++;
		}
	}
	return (0);
}
