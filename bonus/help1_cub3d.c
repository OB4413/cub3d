/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help1_cub3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:23:06 by obarais           #+#    #+#             */
/*   Updated: 2025/09/01 17:47:42 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
	if (game->map[map_y][map_x] == 'D')
		return (1);
	if (game->map[map_y][map_x] == 'C')
		return (0);
	if (game->map[map_y][map_x] != '0'
		&& game->map[map_y][map_x] != game->player_char)
		return (1);
	return (game->map[map_y][map_x] == '1');
}

void	normalize_angle(t_game *game)
{
	if (game->ray_angle < 0)
		game->ray_angle += 2 * M_PI;
	if (game->ray_angle >= 2 * M_PI)
		game->ray_angle -= 2 * M_PI;
	if (game->angle < 0)
		game->angle += 2 * M_PI;
	if (game->angle >= 2 * M_PI)
		game->angle -= 2 * M_PI;
}

int	ftk_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	check_the_dor(t_game *g, double y, double x, int v)
{
	int	facing_down;
	int	facing_right;
	int	map_y;
	int	map_x;

	facing_down = (g->ray_angle > 0 && g->ray_angle < M_PI);
	facing_right = (g->ray_angle < M_PI / 2 || g->ray_angle > 3 * M_PI / 2);
	if (v)
	{
		if (!facing_right)
			x -= TILE;
	}
	else
	{
		if (!facing_down)
			y -= TILE;
	}
	map_y = (int)(y / TILE);
	map_x = (int)(x / TILE);
	if (g->map[map_y][map_x] == 'D')
		return (1);
	return (0);
}

void	open_and_close_door(t_game *g)
{
	int		px;
	int		py;
	int		dist_x;
	int		dist_y;
	double	dist;

	px = (int)(g->player_x + cos(g->angle) * TILE) / TILE;
	py = (int)(g->player_y + sin(g->angle) * TILE) / TILE;
	if (g->map[(int)g->player_y / TILE][(int)g->player_x / TILE] == 'C')
		return ;
	dist_x = (g->player_x / TILE) - px;
	dist_y = (g->player_y / TILE) - py;
	dist = sqrt(dist_x * dist_x + dist_y * dist_y) * TILE;
	if (g->map[py][px] == 'D' && dist <= TILE)
		g->map[py][px] = 'C';
	else if (g->map[py][px] == 'C' && dist <= TILE)
		g->map[py][px] = 'D';
}
