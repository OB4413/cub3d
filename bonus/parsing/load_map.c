/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:44:15 by ynadime           #+#    #+#             */
/*   Updated: 2025/08/25 19:37:00 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

bool	has_invalid_character(char *row)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (row[i] != '1' && row[i] != '0' && row[i] != 'D' && row[i] != 'N'
			&& row[i] != 'S' && row[i] != 'E' && row[i] != 'W'
			&& !ft_isspace(row[i]))
			return (1);
		i++;
	}
	return (0);
}

void	add_row_to_map(t_game *game, char *row)
{
	int		i;
	char	**new_map;

	i = 0;
	while (game->map && game->map[i])
		i++;
	new_map = ft_malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (game->map && game->map[i])
	{
		new_map[i] = game->map[i];
		i++;
	}
	new_map[i] = row;
	new_map[i + 1] = NULL;
	game->map = new_map;
}

int	load_map(t_game *game, int fd)
{
	char	*line;

	line = ft_strtrim(get_next_line(fd), "\n");
	while (line && is_empty_line(line))
		line = ft_strtrim(get_next_line(fd), "\n");
	while (line && !is_empty_line(line))
	{
		if (has_invalid_character(line))
			return (ft_putstr_fd("Error!\nThe map has invalid character.\n", 2),
				2);
		add_row_to_map(game, line);
		line = ft_strtrim(get_next_line(fd), "\n");
	}
	if (!game->map)
		return (ft_putstr_fd("Error!\nNo map has been found.\n", 2), 1);
	while (line)
	{
		if (!is_empty_line(line))
			return (ft_putstr_fd("Error!\nData after the map.\n", 2), 1);
		line = ft_strtrim(get_next_line(fd), "\n");
	}
	return (check_map(game));
}
