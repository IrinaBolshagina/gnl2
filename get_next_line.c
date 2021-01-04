/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 21:29:20 by mhogg             #+#    #+#             */
/*   Updated: 2021/01/03 23:24:18 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_fill_line(char *str, char *remain, char **line)
{
	char	*end;
	int		a;

	a = 0;
	if ((end = ft_strchr(str, '\n')))
	{
		*end = '\0';
		if (!(*line = ft_strjoin(*line, str)))
		{
			free(*line);
			return (-1);
		}
		ft_strcpy(remain, ++end);
		a = 1;
	}
	else	if (!(*line = ft_strjoin(*line, str)))
	{
		free(*line);
		return (-1);
	}
	return (a);
}

int	get_next_line(int fd, char **line)
{
	char		buff[BUFFER_SIZE + 1];
	static char	remain[BUFFER_SIZE + 1];
	int			rb;
	int			flag;

	if (BUFFER_SIZE <= 0 || !line || fd < 0 || read(fd, 0, 0) < 0)
		return (-1);
	*line = malloc(1);
	if (!*line)
		return (-1);
	**line = '\0';
	if ((flag = ft_fill_line(remain, remain, line)) == -1)
		return (-1);
	while (!flag && (rb = read(fd, buff, BUFFER_SIZE)))
	{
		buff[rb] = '\0';
		if ((flag = ft_fill_line(buff, remain, line)) == -1)
			return (-1);
	}
	if (flag == 0)
	{
		*remain = '\0';
		return (0);
	}
	return (1);
}
