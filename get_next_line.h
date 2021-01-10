/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:38 by ashea             #+#    #+#             */
/*   Updated: 2020/05/26 20:36:09 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1000
# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *src);
char	*ft_strljoin(char *s1, char *s2, size_t len);
int		ft_clean(char **buffer, char **line);
int		ft_record(char **buffer, char **line, int endbuffer);
int		get_next_line(int fd, char **line);

#endif
