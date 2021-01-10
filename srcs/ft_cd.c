/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:50:29 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/10 19:08:11 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/buildins.h"

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
			if (!(env_var = ft_strdup(env[i] + ft_strlen(name) + 1)))
				return (NULL);
			break ;
		}
		i++;
	}
	return (env_var);
}

void	ft_update_env(char **env)
{
	char	new_dir[PATH_MAX];
	char	old_dir[PATH_MAX];
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	getcwd(new_dir, PATH_MAX);
	while (env[i])
	{
		path = ft_strchr(env[i], '=') + 1;
		if (!(ft_strncmp(env[i++], "PWD=", 4)))
		{
			ft_strlcpy(old_dir, path, PATH_MAX);
			ft_strlcpy(path, new_dir, PATH_MAX);
		}
	}
	if (!(ft_strncmp(env[i - 1], "OLDPWD=", 7)))
		ft_strlcpy(path, old_dir, PATH_MAX);
	else
	{
		env[i] = ft_strjoin("OLDPWD=", old_dir);
		env[++i] = '\0';
	}
}

int		ft_cd(char **args, char **env)
{
	char	*new_path;
	char	old_dir[PATH_MAX];
	int		return_var;

	new_path = (char*)args[1];
	getcwd(old_dir, PATH_MAX);
	return_var = 0;
	if (!new_path)
	{
		if (!(new_path = ft_getenv("HOME", env)))
			ft_putstr_fd("No 'HOME' var in environment", 1);
	}
	if ((return_var = chdir(new_path)))
	{
		ft_putstr_fd("Can't open dir: ", 1);
		ft_putstr_fd(new_path, 1);
		ft_putchar_fd('\n', 1);
	}
	ft_update_env(env);
	free(new_path);
	return (return_var);
}