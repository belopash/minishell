/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:19:00 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/21 19:53:39 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "./libft.h"

char	*ft_pathjoin(char *path1, char *path2);
char	**ft_toarray(t_list *list);
t_list	*ft_tolist(char **arr);
int		ft_arrlen(void **arr);
int		error(char *name, char *error);
int		print_name(void);
void	putnlandname(void);
void	del(void);

#endif
