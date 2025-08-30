/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 09:13:37 by obarais           #+#    #+#             */
/*   Updated: 2025/08/30 12:15:25 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	update_position_player(t_game *game)
{
	int	x;
	int	y;

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
	game->map[y][x] = '0';
	x = game->player_x / TILE;
	y = game->player_y / TILE;
	game->map[y][x] = game->player_char;
	return (0);
}

void	move_player11(t_game *game, double angle_offset)
{
	double	nx;
	double	ny;

	nx = game->player_x + cos(game->angle + angle_offset) * SPED;
	ny = game->player_y + sin(game->angle + angle_offset) * SPED;
	if (!is_wall(nx, ny, game, angle_offset) && ny > TILE && nx > TILE)
	{
		game->player_x = nx;
		game->player_y = ny;
	}
}

int	prees_key(int key, t_game *game)
{
	if (key == 65307)
	{
		cleanup_game(game);
		exit(0);
	}
	game->keys[key] = 1;
	if (game->keys[101])
		game->shot = 1;
	return (0);
}

int	release_key(int key, t_game *game)
{
	game->keys[key] = 0;
	if (!game->keys[101])
	{
		game->shot = 0;
		game->h = 0;
	}
	return (0);
}
