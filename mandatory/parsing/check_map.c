/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:40:57 by ynadime           #+#    #+#             */
/*   Updated: 2025/08/24 15:40:58 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	is_cell_surrounded(char **map, int x, int y)
{
	if ((x - 1) < 0 || ft_isspace(map[y][x - 1]))
		return (false);
	if (!map[y][x + 1] || ft_isspace(map[y][x + 1]))
		return (false);
	if ((y - 1) < 0 || ft_strlen(map[y - 1]) <= (size_t)x
		|| ft_isspace(map[y - 1][x]))
		return (false);
	if (!map[y + 1] || ft_strlen(map[y + 1]) <= (size_t)x
		|| ft_isspace(map[y + 1][x]))
		return (false);
	return (true);
}

int	validate_map_surroundings(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
					|| map[y][x] == 'E' || map[y][x] == 'W')
				&& !is_cell_surrounded(map, x, y))
			{
				return (ft_putstr_fd("Error!\nThe map is not closed.\n", 2), 1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_player_spawn(t_game *game, int i, int j)
{
	int	player_count;

	player_count = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player_char = game->map[i][j];
				game->player_x = j;
				game->player_y = i;
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count > 1)
		return (ft_putstr_fd("Error!\nMultiple player spawns.\n", 2), 1);
	else if (player_count == 0)
		return (ft_putstr_fd("Error!\nNo player spawn found\n", 2), 1);
	return (0);
}

int	check_map(t_game *game)
{
	if (validate_player_spawn(game, 0, 0)
		|| validate_map_surroundings(game->map))
		return (1);
	return (0);
}
