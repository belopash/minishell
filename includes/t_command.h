/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:42:15 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/10 18:29:38 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_COMMAND_H
#define T_COMMAND_H

#include "./libft.h"

typedef struct s_command
{
	int input;
	int output;
	t_list *list;
} t_command;

#endif
