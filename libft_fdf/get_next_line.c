/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:21:27 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/19 15:53:28 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_newline(int fd, char **line, char **save)
{
	size_t		len;
	char		*tmp;

	len = 0;
	while (save[fd][len] != '\n' && save[fd][len] != '\0')
		++len;
	if (save[fd][len] == '\n')
	{
		tmp = save[fd];
		*line = ft_strsub(tmp, 0, len);
		tmp = ft_strdup(save[fd] + len + 1);
		free(save[fd]);
		save[fd] = tmp;
		if (save[fd][0] == '\0')
			ft_strdel(&save[fd]);
	}
	else
	{
		*line = ft_strdup(save[fd]);
		ft_strdel(&save[fd]);
	}
	return (1);
}

static ssize_t	ft_reader(const int fd, char **save, char *buffer)
{
	ssize_t		bytes_read;
	char		*tmp;

	bytes_read = read(fd, buffer, BUFF_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!save[fd])
			save[fd] = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(save[fd], buffer);
			free(save[fd]);
			save[fd] = tmp;
		}
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFF_SIZE);
	}
	return (bytes_read);
}

int	get_next_line(const int fd, char **line)
{
	static char		*save[MAX_FD];
	ssize_t			bytes_read;
	char			buffer[BUFF_SIZE + 1];

	if (fd < 0 || fd >= MAX_FD || !line || BUFF_SIZE <= 0)
		return (-1);
	bytes_read = ft_reader(fd, save, buffer);
	if (bytes_read < 0)
		return (-1);
	if (bytes_read == 0 && save[fd] == NULL)
	{
		return (0);
	}
	return (ft_newline(fd, line, save));
}
