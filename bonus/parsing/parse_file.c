/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:44:18 by ynadime           #+#    #+#             */
/*   Updated: 2025/08/26 11:16:32 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

int	parse_file(char *path, t_game *game)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error!\nFailed to open map file.\n", 2);
		return (1);
	}
	if (load_config(game, fd) || load_map(game, fd))
		return (close(fd), 1);
	close(fd);
	return (0);
}
