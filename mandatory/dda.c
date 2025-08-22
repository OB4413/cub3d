/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 09:18:54 by obarais           #+#    #+#             */
/*   Updated: 2025/08/13 11:26:48 by obarais          ###   ########.fr       */
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

void	the_distance_with_x(t_game *game, int i, double xn, double yn)
{
	int map_x, map_y, fx;
	double step_x, step_y;
	int facing_right, facing_down;
	facing_down = (game->ray_angle > 0 && game->ray_angle < M_PI);
	facing_right = (game->ray_angle < M_PI / 2 || game->ray_angle > 3 * M_PI
			/ 2);
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
		if (game->map[map_y][map_x] == '1')
			break ;
		xn += step_x;
		yn += step_y;
	}
	game->xa = yn;
	game->xb = xn;
	game->distances_x = sqrt(pow(xn - game->player_x, 2) + pow(yn
				- game->player_y, 2));
}

void	the_distance_with_y(t_game *game, int i, double xn, double yn)
{
	int map_x, map_y, fx;
	double step_x, step_y;
	int facing_right, facing_down;
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
		if (game->map[map_y][map_x] == '1')
			break ;
		xn += step_x;
		yn += step_y;
	}
	game->ya = yn;
	game->yb = xn;
	game->distances_y = sqrt(pow(xn - game->player_x, 2) + pow(yn
				- game->player_y, 2));
}
