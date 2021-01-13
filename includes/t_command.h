/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:42:15 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/13 18:45:27 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_COMMAND_H
#define T_COMMAND_H

#include "./libft.h"

#define DEFAULT 0
#define PIPE 01
#define REDIRECT 010
#define REDPIPE 011

typedef struct s_flags
{
	int redir_r;
	int redir_l;
} t_flags;


typedef struct s_command
{
	int input;
	int output;
	t_list *list;
	int type;
	char *filename;
	t_flags flags;
} t_command;

#endif