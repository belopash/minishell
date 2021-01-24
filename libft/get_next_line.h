/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 13:05:49 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/23 12:56:40 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef unsigned char	t_byte;

# define BUFFER_SIZE 32

int						get_next_line(int fd, char **line);
long					ft_strclen_gnl(const char *str, int c);
void					*ft_memcpy_gnl(void *dst, const void *src, size_t n);
char					*ft_strjoin_gnl(char const *s1, char const *s2);
char					*ft_strdup_gnl(const char *str);
void					ft_free_gnl(char **ptr);

#endif
