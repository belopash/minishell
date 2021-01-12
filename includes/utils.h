/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:19:00 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/12 12:17:39 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

char *ft_pathjoin(char *path1, char *path2);
char **ft_toarray(t_list *list);
t_list *ft_tolist(char **arr);

#endif