/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_imag_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:27:40 by obarais           #+#    #+#             */
/*   Updated: 2025/08/23 19:19:35 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_minimap(t_game *g)
{
	int min_x = g->player_x / TILE;
	int min_y = g->player_y / TILE;

	min_x = (min_x * MINTILE) - (MINMAP_WI / 2);
	min_y = (min_y * MINTILE) - (MINMAP_HE / 2);
	int x = 0;
	int y = 0;
	if (min_x < 0 || min_y < 0)
	{
		if (min_x < 0)
			min_x = 0;
		if (min_y < 0)
			min_y = 0;
	}
	if ((min_y + MINMAP_HE) / MINTILE > g->i - 1 || (min_x + MINMAP_WI) / MINTILE > ftk_strlen(g->map[min_y/ MINTILE]))
	{
		if ((min_y + MINMAP_HE) / MINTILE > g->i - 1)
		{
			if (MINMAP_HE < g->i * MINTILE)
				min_y -= (min_y + MINMAP_HE) - (g->i * MINTILE);
		}
		if ((min_x + MINMAP_WI) / MINTILE > ftk_strlen(g->map[min_y/ MINTILE]))
		{
			if (MINMAP_WI < ftk_strlen(g->map[min_y/ MINTILE]) * MINTILE)
				min_x -= (min_x + MINMAP_WI) - (ftk_strlen(g->map[min_y/ MINTILE]) * MINTILE);
		}
	}
	int i = min_x;
	int j = min_y;
	while (j <= min_y + MINMAP_HE && j < g->i * MINTILE && y < MINMAP_HE)
	{
		i = min_x;
		x = 0;
		while (i <= min_x + MINMAP_WI && i < ftk_strlen(g->map[min_y/ MINTILE]) * MINTILE && x < MINMAP_WI)
		{
			char *dst = g->d_imag + (y * g->size_line + x * (g->bits_per_pixel / 8));
			if (g->map[j / MINTILE] && g->map[j / MINTILE][i / MINTILE] == '1')
				*(unsigned int *)dst = 0xffffff;
			else if (g->map[j / MINTILE] && (g->map[j / MINTILE][i / MINTILE] == 'D' || g->map[j / MINTILE][i / MINTILE] == 'C'))
				*(unsigned int *)dst = 0xff0000;
			else if (g->map[j / MINTILE] && (g->map[j / MINTILE][i / MINTILE] == '0' || g->map[j / MINTILE][i / MINTILE] == g->player_char))
				*(unsigned int *)dst = 0xff00ff;
			else
				*(unsigned int *)dst = 0x000000;
			i++;
			x++;
		}
		y++;
		j++;
	}

	double mi_x = g->player_x / TILE;
	double mi_y = g->player_y / TILE;
	int mn_x = (int)(mi_x * MINTILE) - min_x;
	int mn_y = (int)(mi_y * MINTILE) - min_y;

	int dy = -1;
	int dx = -1;
	int px, py;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			px = mn_x + dx;
			py = mn_y + dy;
			if (px >= 0 && px < MINMAP_WI && py >= 0 && py < MINMAP_HE)
			{
				char *dst = g->d_imag + (py * g->size_line + px * (g->bits_per_pixel / 8));
				*(unsigned int *)dst = 0x000000;
			}
			dx++;
		}
		dy++;
	}

	double dir_x = cos(g->angle);
	double dir_y = sin(g->angle);
	int k = 0;
	while (k < 6)
	{
		px = mn_x + (int)(dir_x * k);
		py = mn_y + (int)(dir_y * k);
		if (px >= 0 && px < MINMAP_WI && py >= 0 && py < MINMAP_HE)
		{
			char *dst = g->d_imag + (py * g->size_line + px * (g->bits_per_pixel / 8));
			*(unsigned int *)dst = 0x000000;
		}
		k++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->imag, 5, 5);
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

void	drow_imag_player(t_game *g, int x, int y)
{
	char *dst, *st;
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
