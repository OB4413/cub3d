/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2_cub3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:04:53 by obarais           #+#    #+#             */
/*   Updated: 2025/08/25 15:16:04 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	drow_imag_player(t_game *g, int x, int y)
{
	char *(dst), *(st);
	if (g->ng == 0)
		g->d_p_imag = mlx_get_data_addr(g->pst_imag[g->h], &g->pbpp, &g->psl,
				&g->pend);
	if (g->ng == 1)
		g->d_p_imag = mlx_get_data_addr(g->ak_imag[g->h], &g->pbpp, &g->psl,
				&g->pend);
	if (g->ng == 2)
		g->d_p_imag = mlx_get_data_addr(g->mg_imag[g->h], &g->pbpp, &g->psl,
				&g->pend);
	while (y++ <= WIN_HEIGHT)
	{
		x = 0;
		while (x <= WIN_WIDTH)
		{
			dst = g->d_p_imag + (y * g->psl + x * (g->pbpp / 8));
			if (*(unsigned int *)dst != 0x01fefe)
			{
				st = g->d_imag_v + (y * g->sl + x * (g->bpp / 8));
				*(unsigned int *)st = *(unsigned int *)dst;
			}
			x++;
		}
	}
	help_drow_imag_player(g);
}

void	help_drow_imag_player(t_game *g)
{
	static int	n = 0;

	if (g->shot == 1)
	{
		if (n++ == 2)
		{
			n = 0;
			g->h++;
		}
		if (g->ng == 0)
		{
			if (g->pst_imag[g->h] == NULL)
				g->h = 0;
		}
		if (g->ng == 1)
		{
			if (g->ak_imag[g->h] == NULL)
				g->h = 0;
		}
		if (g->ng == 2)
		{
			if (g->mg_imag[g->h] == NULL)
				g->h = 0;
		}
	}
}

void	help_raycaster(t_game *game, int x)
{
	void	*image;
	int		y;

	while (game->map[game->i])
		game->i++;
	change_line_to_null(game);
	chose_the_angle_p(game);
	init_imag_player(game, 0, 0);
	game->player_x = (game->player_x * TILE) + TILE / 2;
	game->player_y = (game->player_y * TILE) + TILE / 2;
	game->imag = mlx_new_image(game->mlx, (int)MINMAP_WI, (int)MINMAP_HE);
	game->imag_v = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	image = mlx_xpm_file_to_image(game->mlx, "textures/open_game.xpm", &x, &y);
	if (!image || !game->imag_v || !game->imag)
	{
		//ft_malloc(0, free, game);
		exit(0);
	}
	game->d_imag = mlx_get_data_addr(game->imag, &game->bits_per_pixel,
			&game->size_line, &game->endian);
	game->d_imag_v = mlx_get_data_addr(game->imag_v, &game->bpp, &game->sl,
			&game->en);
	mlx_put_image_to_window(game->mlx, game->win, image, 0, 0);
	sleep(5);
	mlx_destroy_image(game->mlx, image);
}

double	help_dda(t_game *g, int facing_right)
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

void	help4_drow_minimap(t_game *g, char *dst, int i, int j)
{
	if (g->map[j / MINTILE] && g->map[j / MINTILE][i / MINTILE] == '1')
		*(unsigned int *)dst = 0xffffff;
	else if (g->map[j / MINTILE] && (g->map[j / MINTILE][i / MINTILE]
		== 'D' || g->map[j / MINTILE][i / MINTILE] == 'C'))
		*(unsigned int *)dst = 0xff0000;
	else if (g->map[j / MINTILE] && (g->map[j / MINTILE][i / MINTILE]
		== '0' || g->map[j / MINTILE][i / MINTILE] == g->player_char))
		*(unsigned int *)dst = 0xff00ff;
	else
		*(unsigned int *)dst = 0x000000;
}
