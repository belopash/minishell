/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_buildin.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:18:01 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/08 13:53:39 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_BUILIN_H
#define T_BUILIN_H

typedef struct s_buildin
{
    char *name;
    int (*command)(char **argv, char **envp);
} t_buildin;

int execbi(char *name, char **args, char **envp);

#endif