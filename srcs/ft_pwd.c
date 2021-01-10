/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:20:55 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/08 15:15:40 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include "../includes/libft.h"
#include "../includes/buildin_commands.h"

int ft_pwd(char **args, char** env)
{
    char buf[PATH_MAX + 1];

    if (!getcwd(buf, PATH_MAX))
        return -1;
    write(1, buf, ft_strlen(buf));
    write(1, "\n", 1);
    return 0;
}