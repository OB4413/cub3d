/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:09:06 by ynadime           #+#    #+#             */
/*   Updated: 2025/05/10 19:20:31 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*setline(char **stock)
{
	char	*tmp;
	char	*newline;
	char	*line;

	if (!*stock)
		return (NULL);
	newline = ft_strchr(*stock, '\n');
	if (newline)
	{
		line = ft_substr(*stock, 0, (newline - *stock) + 1);
		tmp = *stock;
		if (*(newline + 1))
			*stock = ft_strdup(newline + 1);
		else
			*stock = NULL;
		return (free(tmp), line);
	}
	else if (**stock)
	{
		line = ft_strdup(*stock);
		return (free(*stock), *stock = NULL, line);
	}
	free(*stock);
	*stock = NULL;
	return (NULL);
}

ssize_t	fill_stock(int fd, ssize_t bytesread, char **stock, char *buffer)
{
	char	*tmp;

	if (!*stock)
		return (0);
	while (bytesread)
	{
		if (bytesread < 0)
			return (1);
		buffer[bytesread] = '\0';
		tmp = *stock;
		*stock = ft_strjoin(*stock, buffer);
		free(tmp);
		if (ft_strchr(*stock, '\n'))
			return (0);
		bytesread = read(fd, buffer, BUFFER_SIZE);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stock[1024];
	char		*buffer;
	ssize_t		bytesread;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
		return (NULL);
	buffer = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!stock[fd])
		stock[fd] = ft_strdup("");
	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread)
	{
		if (fill_stock(fd, bytesread, &stock[fd], buffer))
		{
			free(stock[fd]);
			stock[fd] = NULL;
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (setline(&stock[fd]));
}
