/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 21:29:20 by mhogg             #+#    #+#             */
/*   Updated: 2020/12/29 22:48:24 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_check_remain(char *remain, char **line)
{
	char	*end;

	*line = (malloc(1));
	(*line)[0] = '\0';
	end = NULL;
	if ((end = ft_strchr(remain, '\n')))
	{
		*end = '\0';
		*line = ft_strjoin(*line, remain);
		ft_strcpy(remain, ++end);
	}
	else
		*line = ft_strjoin(*line, remain);
	return (end);
}

int		ft_free_remain(char *remain)
{
	remain[0] = '\0';
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char		buff[BUFFER_SIZE + 1];
	int			rb;
	char		*end;
	static char	remain[BUFFER_SIZE + 1];

	rb = 1;
	if (line == NULL || read(fd, 0, 0) < 0)
		return (-1);
	end = ft_check_remain(remain, line);
	while (!end && (rb = read(fd, buff, BUFFER_SIZE)))
	{
		buff[rb] = '\0';
		if ((end = ft_strchr(buff, '\n')))
		{
			*end = '\0';
			ft_strcpy(remain, ++end);
		}
		if (!(*line = ft_strjoin(*line, buff)))
			return (-1);
	}
	if (rb == 0)
		return (ft_free_remain(remain));
	return (1);
}
