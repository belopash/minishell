/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 21:12:00 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/11 17:51:00 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "signal.h"
#include <stdio.h>

int	get_line(char **line, char **mem)
{
	long	len;
	char	*t;
	long	n;

	n = ft_strclen_gnl(*mem, '\n');
	len = ft_strclen_gnl(*mem, '\0');
	if (!(*line = malloc((n + 1) * sizeof(char)))
		|| !(t = malloc((len - n) * sizeof(char))))
	{
		ft_free_gnl(line);
		return (-1);
	}
	ft_memcpy_gnl(*line, *mem, n);
	(*line)[n] = '\0';
	ft_memcpy_gnl(t, *mem + n + 1, len - n);
	ft_free_gnl(mem);
	*mem = t;
	return (1);
}

int	read_until_line(int fd, char **line, char **mem, char **buf)
{
	char	*t;
	int		ret;

	if (!(*buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	if (ft_strclen_gnl(*mem, '\n') >= 0)
		return (get_line(line, mem));
	while ((ret = read(fd, *buf, BUFFER_SIZE)) >= 0)
	{
		*(*buf + ret) = '\0';
		if (!(t = ft_strjoin_gnl(*mem, *buf)))
			return (-1);
		ft_free_gnl(mem);
		*mem = t;
		if (ft_strclen_gnl(*buf, '\n') >= 0)
			return (get_line(line, mem));
		if (ret == 0)
		{
			*line = *mem;
			return (0);
		}
	}
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char	*mem = NULL;
	int			ret;
	char		*buf;

	if (fd < 0 || !line)
	{
		ft_free_gnl(&mem);
		return (-1);
	}
	ret = read_until_line(fd, line, &mem, &buf);
	ft_free_gnl(&buf);
	if (ret < 0)
		ft_free_gnl(&mem);
	return (ret);
}
