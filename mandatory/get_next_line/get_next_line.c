/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:20:48 by ynadime           #+#    #+#             */
/*   Updated: 2025/08/26 11:08:45 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		return (ft_free(tmp), line);
	}
	else if (**stock)
	{
		line = ft_strdup(*stock);
		return (ft_free(*stock), *stock = NULL, line);
	}
	ft_free(*stock);
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
		ft_free(tmp);
		if (ft_strchr(*stock, '\n'))
			return (0);
		bytesread = read(fd, buffer, BUFFER_SIZE);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*buffer;
	ssize_t		bytesread;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = (char *)ft_malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!stock)
		stock = ft_strdup("");
	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread)
	{
		if (fill_stock(fd, bytesread, &stock, buffer))
		{
			ft_free(stock);
			stock = NULL;
			ft_free(buffer);
			return (NULL);
		}
	}
	ft_free(buffer);
	return (setline(&stock));
}
