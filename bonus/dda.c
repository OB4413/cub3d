/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:03:37 by obarais           #+#    #+#             */
/*   Updated: 2025/08/13 12:10:22 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	the_distance_with_x(t_game *game, int i)
{
	double	distance;
	int		facing_right;
	int		facing_down;
	int		fx;

	double xn, yn;
	int map_x, map_y;
	double step_x, step_y;
	facing_right = (game->ray_angle < M_PI / 2 || game->ray_angle > 3 * M_PI
			/ 2);
	facing_down = (game->ray_angle > 0 && game->ray_angle < M_PI);
	xn = floor(game->player_x / TILE) * TILE;
	if (facing_right)
		xn += TILE;
	yn = tan(game->ray_angle) * (xn - game->player_x) + game->player_y;
	step_x = TILE;
	if (!facing_right)
		step_x *= -1;
	step_y = step_x * tan(game->ray_angle);
	if ((!facing_down && step_y > 0) || (facing_down && step_y < 0))
		step_y *= -1;
	while (1)
	{
		map_x = (int)xn / TILE;
		map_y = (int)yn / TILE;
		if (!facing_right)
			map_x -= 1;
		if (map_y < 0 || map_y >= i || !game->map[map_y])
			break ;
		fx = ftk_strlen(game->map[map_y]);
		if (map_x < 0 || map_x >= fx)
			break ;
		if (game->map[map_y][map_x] != '0' && game->map[map_y][map_x] != 'C')
			break ;
		xn += step_x;
		yn += step_y;
	}
	game->xa = yn;
	game->xb = xn;
	distance = sqrt(pow(xn - game->player_x, 2) + pow(yn - game->player_y, 2));
	game->distances_x = distance;
}

void	the_distance_with_y(t_game *game, int i)
{
	double	distance;
	int		facing_down;
	int		facing_right;
	int		fx;

	double xn, yn;
	int map_x, map_y;
	double step_x, step_y;
	facing_down = (game->ray_angle > 0 && game->ray_angle < M_PI);
	facing_right = (game->ray_angle < M_PI / 2 || game->ray_angle > 3 * M_PI
			/ 2);
	yn = floor(game->player_y / TILE) * TILE;
	if (facing_down)
		yn += TILE;
	xn = game->player_x + (yn - game->player_y) / tan(game->ray_angle);
	step_y = TILE;
	if (!facing_down)
		step_y *= -1;
	step_x = step_y / tan(game->ray_angle);
	if ((!facing_right && step_x > 0) || (facing_right && step_x < 0))
		step_x *= -1;
	while (1)
	{
		map_x = (int)xn / TILE;
		map_y = (int)yn / TILE;
		if (!facing_down)
			map_y -= 1;
		if (map_y < 0 || map_y >= i || !game->map[map_y])
			break ;
		fx = ftk_strlen(game->map[map_y]);
		if (map_x < 0 || map_x >= fx)
			break ;
		if (game->map[map_y][map_x] != '0' && game->map[map_y][map_x] != 'C')
			break ;
		xn += step_x;
		yn += step_y;
	}
	game->ya = yn;
	game->yb = xn;
	distance = sqrt(pow(xn - game->player_x, 2) + pow(yn - game->player_y, 2));
	game->distances_y = distance;
}

double	dda(t_game *g)
{
	int	facing_down;
	int	facing_right;

	facing_down = (g->ray_angle > 0 && g->ray_angle < M_PI);
	facing_right = (g->ray_angle < M_PI / 2 || g->ray_angle > 3 * M_PI / 2);
	the_distance_with_y(g, g->i);
	the_distance_with_x(g, g->i);
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
	{
		g->ofs_tex = fmod(g->xa, (double)TILE);
		g->x_or_y = 0;
		if (check_the_dor(g, g->xa, g->xb, 1))
			g->char_color = 'd';
		else if (facing_right)
			g->char_color = 'w';
		else
			g->char_color = 'e';
		return (g->distances_x);
	}
	return (g->distances_y);
}
