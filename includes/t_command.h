/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:42:15 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/12 17:43:50 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_COMMAND_H
#define T_COMMAND_H

#include "./libft.h"

#define DEFAULT 0
#define PIPE 01
#define REDIRECT 010
#define REDPIPE 011

typedef struct s_command
{
	int input;
	int output;
	t_list *list;
	int type;
	char *filename;
} t_command;

#endif