/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2_cub3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:04:53 by obarais           #+#    #+#             */
/*   Updated: 2025/08/22 22:35:29 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	change_the_gane(t_game *g)
{
	g->ng++;
	if (g->ng == 3)
		g->ng = 0;
}

void	help_raycaster(t_game *game)
{
	void	*image;
	int		x;
	int		y;

	while (game->map[game->i])
		game->i++;
	change_line_to_null(game);
	chose_the_angle_p(game);
	game->player_x *= TILE;
	game->player_y *= TILE;
	game->player_x += TILE / 2;
	game->player_y += TILE / 2;
	game->imag = mlx_new_image(game->mlx, (int)MINMAP_WI, (int)MINMAP_HE);
	game->d_imag = mlx_get_data_addr(game->imag, &game->bits_per_pixel,
			&game->size_line, &game->endian);
	game->imag_v = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->d_imag_v = mlx_get_data_addr(game->imag_v, &game->bpp, &game->sl,
			&game->en);
	init_imag_player(game, 0, 0);
	image = mlx_xpm_file_to_image(game->mlx, "textures/open_game.xpm", &x, &y);
	mlx_put_image_to_window(game->mlx, game->win, image, 0, 0);
	sleep(5);
	mlx_destroy_image(game->mlx, image);
}
