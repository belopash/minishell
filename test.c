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
#include "includes/buildins.h"
#include <fcntl.h>


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

char	*ft_getenv(const char *name, char **env)
{
	char	*env_var;
	int		i;

	i = 0;
	env_var = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name)))
		{
			return env[i];
		}
		i++;
	}
	return (NULL);
}

char *ft_pathjoin(char *path1, char *path2)
{
	char *path;
	char *t;

	if (!(t = ft_strjoin(path1, "/")))
		return (NULL);
	if (!(path=ft_strjoin(t, path2)))
		return (NULL);
	free(t);
	return path;
}

int execute(t_command command, char **envp)
{
	int ret;
	struct stat sb;

	char **args = ft_create_array(command.list);
	if (!fork())
	{
		signal(SIGINT, ft_exit);
		dup2(command.input, 0);
		dup2(command.output, 1);
		if (command.input != 0)
			close(command.input);
		if (command.output != 1)
			close(command.output);

		if (execbi(args[0], args, envp) == 0)
			exit(0);

		char **paths = ft_split(ft_getenv("PATH", envp) + 5, ':');
		int valid = 0;
		int i = 0;

		char *path = NULL;
		while (paths[i] && !valid)
		{
			path = ft_pathjoin(paths[i], args[0]);
			if ((stat((const char *)path, &sb) == 0 && (sb.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))))
				valid = 1;
			i++;
		}
		if (!valid)
			exit(-1);

		return execve(path, args, envp);
	}
	if (command.input != 0)
		close(command.input);
	if (command.output != 1)
		close(command.output);
	free(args);
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

int ft_parsing(char *line, char **env)
{
	char *content;
	int i;
	int j;

	content = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
	i = 0;
	j = 0;
	t_command command = (t_command){0, 1, NULL};

	int flag_right_redirect = 0;
	int flag_left_redirect = 0;
	while (line[i])
	{

		if (line[i] == ';')
		{
			if (j > 0)
				ft_add_arg(&j, &content, &flag_right_redirect, &flag_left_redirect, &command);

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
				ft_add_arg(&j, &content, &flag_right_redirect, &flag_left_redirect, &command);
			// ft_putendl_fd(ft_together(command.list), 1);

			int fd_p[2];
			pipe(fd_p);
			if (command.output == 1)
				command.output = fd_p[1];
			else
				dup2(command.output, fd_p[0]);
			execute(command, env);
			command = (t_command){fd_p[0], 1, NULL};

			i++;
			continue;
		}

		if (line[i] == '>')
		{
			if (j > 0)
				ft_add_arg(&j, &content, &flag_right_redirect, &flag_left_redirect, &command);
			flag_right_redirect++;
			;
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
			tmp = ft_search_env(&i, line, env);

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
	execute(command, env);

	int pid;
	int status;

	while ((pid = wait(&status)) > 0)
		;
	return (0);
}

void putnl()
{
	char c = -1;

	write(0, "\n", 1);
}

int ft_minishell(char **env)
{
	char *line;
	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));

	signal(SIGINT, putnl);	
	while (1)
	{
		write(1, "\e[1;34mminishell\e[0m$> ", 23);
		int r = get_next_line(0, &line);
		if (!ft_strlen(line))
			continue;
		if (!ft_strncmp(line, "exit", 4) || r<=0)
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
