/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:09:16 by obarais           #+#    #+#             */
/*   Updated: 2025/09/01 17:48:14 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ftk_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	help_is_wall(double angle_offset, t_game *g, int x, int y)
{
	int	facing_right;
	int	facing_down;

	facing_down = (g->angle + angle_offset > 0 && g->angle
			+ angle_offset < M_PI);
	facing_right = (g->angle + angle_offset < M_PI / 2 || g->angle
			+ angle_offset > 3 * M_PI / 2);
	if (facing_down && facing_right)
	{
		if (g->map[y][x + 1] == '1' && g->map[y + 1][x] == '1')
			return (1);
	}
	else if (facing_down && !facing_right)
	{
		if (g->map[y][x - 1] == '1' && g->map[y + 1][x] == '1')
			return (1);
	}
	else if (!facing_down && facing_right && g->map[y][x + 1]
		== '1' && g->map[y - 1][x] == '1')
		return (1);
	else if (!facing_down && !facing_right && g->map[y][x - 1]
		== '1' && g->map[y - 1][x] == '1')
		return (1);
	return (0);
}

int	is_wall(double x, double y, t_game *game, double angle_offset)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE);
	map_y = (int)(y / TILE);
	if (map_x != (int)game->player_x / TILE && map_y != (int)game->player_y
		/ TILE && game->map[map_y][map_x] != '1')
		return (help_is_wall(angle_offset, game, game->player_x
				/ TILE, game->player_y / TILE));
	return (game->map[map_y][map_x] == '1');
}
