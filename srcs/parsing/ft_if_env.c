/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:28:45 by ashea             #+#    #+#             */
/*   Updated: 2021/01/22 12:28:51 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static char *ft_search_env(int *i, char *line, char **env)
{
    char *var;
    int j;
    int k;

    if (!(var = (char *)malloc(sizeof(char) * (PATH_MAX + 1))))
        exit(-1);
    j = 0;
    while (line[*i] != ' ' && line[*i] != '$' && line[*i] != '"' && line[*i] != '\'' && line[*i] != ';' && line[*i])
    {
        var[j] = line[*i];
        j++;
        (*i)++;
    }
    k = 0;
    while (env[k])
    {
        if (!ft_strncmp(env[k], var, j))
            if (env[k][j] == '=')
                return (ft_strdup(env[k] + j + 1));
        k++;
    }
    return (ft_strdup(""));
}

int ft_if_env(int *j, char *content, char *line, t_shell *shell)
{
    int i;
    char *tmp;
    
    i = 0;
    if (line[i] == '$' && ((line[i + 1] != '$' && line[i + 1] != '\\' && line[i + 1] != ' ' && line[i + 1] != '\'' && line[i + 1] != '"' && line[i + 1] != '\0') || line[i + 1] == '?'))
    {
        i++;
        if (line[i] == '?')
        {
            i++;
            if(!(tmp = ft_strdup(ft_itoa(shell->code))))
                exit(-1);
        }
        else
            if(!(tmp = ft_search_env(&i, line, ft_toarray(shell->env->list))))
                exit(-1);
        while (tmp[0])
        {
            content[*j] = tmp[0];
            tmp++;
            (*j)++;
        }
    }
    return (i);
}
