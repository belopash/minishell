#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdarg.h>
#include "includes/t_buildin.h"
#include <sys/stat.h>
#include "./includes/t_command.h"

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

	var = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
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

int execute(t_command command, char **envp)
{
	int ret;
	struct stat sb;

	char **args = ft_create_array(command.list);
	if (!fork())
	{
		dup2(command.input, 0);
		dup2(command.output, 1);
		if (command.input != 0)
			close(command.input);
		if (command.output != 1)
			close(command.output);

		if (execbi(args[0], args, envp) == 0)
			exit(0);

		if (!(stat((const char *)args[0], &sb) == 0 && (sb.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))))
			exit(-1);

		return execve(args[0], args, envp);
	}
	if (command.input != 0)
		close(command.input);
	if (command.output != 1)
		close(command.output);
	free(args);
}

int ft_parsing(char *line, char **env)
{
	char *content;
	int i;
	int j;

	content = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	i = 0;
	j = 0;
	t_command command = (t_command){0, 1, NULL};
	while (line[i])
	{

		if (line[i] == ';')
		{
			if (j > 0)
			{
				content[j] = '\0';
				ft_lstadd_back(&(command.list), ft_lstnew(ft_strdup(content)));
				j = 0;
			}

			int pid;
			int status;
			execute(command, env);

			while ((pid = wait(&status)) > 0)
				;
			command = (t_command){0, 1, NULL};
			i++;
			continue;
		}

		if (line[i] == '|')
		{
			if (j > 0)
			{
				content[j] = '\0';
				ft_lstadd_back(&(command.list), ft_lstnew(ft_strdup(content)));
				j = 0;
			}
			// ft_putendl_fd(ft_together(command.list), 1);

			int fd_p[2];
			pipe(fd_p);
			if (command.output == 1)
				command.output = fd_p[1];
			execute(command, env);
			command = (t_command){fd_p[0], 1, NULL};

			i++;
			continue;
		}

		if (line[i] == '>')
		{
			if (j > 0)
			{
				content[j] = '\0';
				ft_lstadd_back(&(command.list), ft_lstnew(ft_strdup(content)));
				j = 0;
			}
			i++;
			continue;
		}

		if (line[i] == '<')
		{
			if (j > 0)
			{
				content[j] = '\0';
				ft_lstadd_back(&(command.list), ft_lstnew(ft_strdup(content)));
				j = 0;
			}
			i++;
			continue;
		}

		if (line[i] == '$' && line[i + 1] != '\\' && line[i + 1] != ' ' && line[i + 1] != '\'' && line[i + 1] != '"' && line[i + 1] != '\0')
		{
			i++;
			char *tmp;
			tmp = ft_search_env(&i, line, env);
			while (tmp[0])
			{
				content[j] = tmp[0];
				tmp++;
				j++;
			}
			if ((line[i] == ' ' || line[i] == '\0') && j > 0)
			{
				content[j] = '\0';
				ft_lstadd_back(&(command.list), ft_lstnew(ft_strdup(content)));
				j = 0;
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
					tmp = ft_search_env(&i, line, env);
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
			if ((line[i] == ' ' || line[i] == '\0') && j > 0)
			{
				content[j] = '\0';
				ft_lstadd_back(&(command.list), ft_lstnew(ft_strdup(content)));
				j = 0;
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
			if ((line[i] == ' ' || line[i] == '\0') && j > 0)
			{
				content[j] = '\0';
				ft_lstadd_back(&(command.list), ft_lstnew(ft_strdup(content)));
				j = 0;
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
		if ((line[i] == ' ' || line[i] == '\0') && j > 0)
		{
			content[j] = '\0';
			ft_lstadd_back(&(command.list), ft_lstnew(ft_strdup(content)));
			j = 0;
		}
	}
	char **args = ft_create_array(command.list);
	execute(command, env);

	int pid;
	int status;

	while ((pid = wait(&status)) > 0)
		;
	return (0);
}

int ft_minishell(char **env)
{
	char *line;
	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));

	while (1)
	{
		write(1, "\e[1;34mminishell\e[0m$> ", 23);
		int r = get_next_line(0, &line);
		if (r == 0)
		{
			continue;
		}
		if (!ft_strncmp(line, "exit", 4))
		{
			write(1, "exit\n", 5);
			break;
		}
		ft_parsing(line, env);
	}
	free(line);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	ft_minishell(env);
	return (0);
}
