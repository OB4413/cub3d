/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:11:05 by obarais           #+#    #+#             */
/*   Updated: 2025/08/21 12:24:42 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	chose_the_angle_p(t_game *game)
{
	if (game->player_char == 'N')
		game->angle = 3 * M_PI / 2;
	else if (game->player_char == 'S')
		game->angle = M_PI / 2;
	else if (game->player_char == 'E')
		game->angle = 0;
	else if (game->player_char == 'W')
		game->angle = M_PI;
}

int	prees_key(int key, t_game *game)
{
	if (key == 65307)
		exit(0);
	game->keys[key] = 1;
	if (game->keys[101])
		open_and_close_door(game);
	if (game->keys[121])
		change_the_gane(game);
	if (game->keys[113])
		game->ng = 4;
	if (key == 99)
		game->jump = (WIN_HEIGHT / 2) - 200;
	return (0);
}

int	release_key(int key, t_game *game)
{
	game->keys[key] = 0;
	if (key == 99)
		game->jump = WIN_HEIGHT / 2;
	return (0);
}

void	move_player11(t_game *game, double angle_offset)
{
	double	nx;
	double	ny;
	double	a;
	double	b;

	nx = cos(game->angle + angle_offset) * SPED;
	ny = sin(game->angle + angle_offset) * SPED;
	a = game->player_x + nx;
	b = game->player_y + ny;
	if (!is_wall(a, b, game) && a > TILE && b > TILE)
	{
		game->player_x += nx;
		game->player_y += ny;
	}
	else
	{
		nx = cos(game->angle + angle_offset) * SPED / 2;
		ny = sin(game->angle + angle_offset) * SPED / 2;
		a = game->player_x + nx;
		b = game->player_y + ny;
		if (!is_wall(game->player_x, b, game) && b > TILE)
			game->player_y += ny;
		else if (!is_wall(a, game->player_y, game) && a > TILE)
			game->player_x += nx;
	}
}

int	update_position_player(t_game *game, int x, int y)
{
	x = game->player_x / TILE;
	y = game->player_y / TILE;
	if (game->keys[65363])
		game->angle += SPED_RL;
	if (game->keys[65361])
		game->angle -= SPED_RL;
	if (game->keys[119])
		move_player11(game, 0);
	if (game->keys[115])
		move_player11(game, M_PI);
	if (game->keys[100])
		move_player11(game, M_PI / 2);
	if (game->keys[97])
		move_player11(game, -M_PI / 2);
	if (game->keys[32] && game->jump == WIN_HEIGHT / 2)
		game->index_jumb = 1;
	if (game->map[y][x] != 'C' && game->map[y][x] != 'D')
	{
		game->map[y][x] = '0';
		x = game->player_x / TILE;
		y = game->player_y / TILE;
		if (game->map[y][x] != 'C' && game->map[y][x] != 'D')
			game->map[y][x] = game->player_char;
	}
	return (0);
}
