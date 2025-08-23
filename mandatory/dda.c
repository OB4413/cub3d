/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 09:18:54 by obarais           #+#    #+#             */
/*   Updated: 2025/08/23 10:57:11 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	dda(t_game *game, int facing_down, int facing_right)
{
	facing_down = (game->ray_angle > 0 && game->ray_angle < M_PI);
	facing_right = (game->ray_angle < M_PI / 2 || game->ray_angle > 3 * M_PI
			/ 2);
	the_distance_with_y(game, game->i, 0, 0);
	the_distance_with_x(game, game->i, 0, 0);
	if (game->distances_x > game->distances_y)
	{
		game->ofs_tex = fmod(game->yb, (double)TILE);
		if (facing_down)
			game->char_color = 'n';
		else
			game->char_color = 's';
		return (game->distances_y);
	}
	else
	{
		game->ofs_tex = fmod(game->xa, (double)TILE);
		if (facing_right)
			game->char_color = 'w';
		else
			game->char_color = 'e';
		return (game->distances_x);
	}
	return (game->distances_y);
}

void	help_the_distance_with_x(t_game *g, double step_x, double step_y, int i)
{
	int	fx;
	int	map_x;
	int	map_y;
	int	facing_right;

	facing_right = (g->ray_angle < M_PI / 2 || g->ray_angle > 3 * M_PI / 2);
	while (1)
	{
		map_x = (int)g->xb / TILE;
		map_y = (int)g->xa / TILE;
		if (!facing_right)
			map_x -= 1;
		if (map_y < 0 || map_y >= i || !g->map[map_y])
			break ;
		fx = ftk_strlen(g->map[map_y]);
		if (map_x < 0 || map_x >= fx)
			break ;
		if (g->map[map_y][map_x] == '1')
			break ;
		g->xb += step_x;
		g->xa += step_y;
	}
	g->distances_x = sqrt(pow(g->xb - g->player_x, 2) + pow(g->xa - g->player_y,
				2));
}

void	the_distance_with_x(t_game *g, int i, double step_x, double step_y)
{
	int	facing_right;
	int	facing_down;

	facing_down = (g->ray_angle > 0 && g->ray_angle < M_PI);
	facing_right = (g->ray_angle < M_PI / 2 || g->ray_angle > 3 * M_PI / 2);
	g->xb = floor(g->player_x / TILE) * TILE;
	if (facing_right)
		g->xb += TILE;
	g->xa = tan(g->ray_angle) * (g->xb - g->player_x) + g->player_y;
	step_x = TILE;
	if (!facing_right)
		step_x *= -1;
	step_y = step_x * tan(g->ray_angle);
	if ((!facing_down && step_y > 0) || (facing_down && step_y < 0))
		step_y *= -1;
	help_the_distance_with_x(g, step_x, step_y, i);
}

void	help_the_distance_with_y(t_game *g, double step_x, double step_y, int i)
{
	int	fx;
	int	map_x;
	int	map_y;
	int	facing_down;

	facing_down = (g->ray_angle > 0 && g->ray_angle < M_PI);
	while (1)
	{
		map_x = (int)g->yb / TILE;
		map_y = (int)g->ya / TILE;
		if (!facing_down)
			map_y -= 1;
		if (map_y < 0 || map_y >= i || !g->map[map_y])
			break ;
		fx = ftk_strlen(g->map[map_y]);
		if (map_x < 0 || map_x >= fx)
			break ;
		if (g->map[map_y][map_x] == '1')
			break ;
		g->yb += step_x;
		g->ya += step_y;
	}
	g->distances_y = sqrt(pow(g->yb - g->player_x, 2) + pow(g->ya - g->player_y,
				2));
}

void	the_distance_with_y(t_game *g, int i, double step_x, double step_y)
{
	int	facing_right;
	int	facing_down;

	facing_down = (g->ray_angle > 0 && g->ray_angle < M_PI);
	facing_right = (g->ray_angle < M_PI / 2 || g->ray_angle > 3 * M_PI / 2);
	g->ya = floor(g->player_y / TILE) * TILE;
	if (facing_down)
		g->ya += TILE;
	g->yb = g->player_x + (g->ya - g->player_y) / tan(g->ray_angle);
	step_y = TILE;
	if (!facing_down)
		step_y *= -1;
	step_x = step_y / tan(g->ray_angle);
	if ((!facing_right && step_x > 0) || (facing_right && step_x < 0))
		step_x *= -1;
	help_the_distance_with_y(g, step_x, step_y, i);
}
