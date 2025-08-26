/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:03:37 by obarais           #+#    #+#             */
/*   Updated: 2025/08/23 11:36:39 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
		if (g->map[map_y][map_x] != '0' && g->map[map_y][map_x] != 'C')
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

	facing_right = (g->ray_angle < M_PI / 2 || g->ray_angle > 3 * M_PI / 2);
	facing_down = (g->ray_angle > 0 && g->ray_angle < M_PI);
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
		if (g->map[map_y][map_x] != '0' && g->map[map_y][map_x] != 'C')
			break ;
		g->yb += step_x;
		g->ya += step_y;
	}
	g->distances_y = sqrt(pow(g->yb - g->player_x, 2) + pow(g->ya - g->player_y,
				2));
}

void	the_distance_with_y(t_game *g, int i, double step_x, double step_y)
{
	int	facing_down;
	int	facing_right;

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

double	dda(t_game *g, int facing_down, int facing_right)
{
	facing_down = (g->ray_angle > 0 && g->ray_angle < M_PI);
	facing_right = (g->ray_angle < M_PI / 2 || g->ray_angle > 3 * M_PI / 2);
	the_distance_with_y(g, g->i, 0.0, 0.0);
	the_distance_with_x(g, g->i, 0.0, 0.0);
	if (g->distances_x > g->distances_y)
	{
		g->ofs_tex = fmod(g->yb, (double)TILE);
		g->x_or_y = 1;
		if (check_the_dor(g, g->ya, g->yb, 0))
			g->char_color = 'd';
		else if (facing_down)
			g->char_color = 'n';
		else
			g->char_color = 's';
		return (g->distances_y);
	}
	else
		return (help_dda(g, facing_right));
	return (g->distances_y);
}
