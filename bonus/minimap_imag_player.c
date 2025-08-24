/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_imag_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:27:40 by obarais           #+#    #+#             */
/*   Updated: 2025/08/24 11:39:58 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	help_drow_minimap(t_game *g, int mn_x, int mn_y, char *dst)
{
	int		dy;
	int		dx;
	int		px;
	int		py;

	dy = -1;
	dx = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			px = mn_x + dx;
			py = mn_y + dy;
			if (px >= 0 && px < MINMAP_WI && py >= 0 && py < MINMAP_HE)
			{
				dst = g->d_imag + (py * g->size_line + px * (g->bits_per_pixel
							/ 8));
				*(unsigned int *)dst = 0x000000;
			}
			dx++;
		}
		dy++;
	}
}

void	help1_drow_minimap(t_game *g, int mn_x, int mn_y, char *dst)
{
	int		px;
	int		py;
	double	dir_x;
	double	dir_y;
	int		k;

	k = 0;
	dir_x = cos(g->angle);
	dir_y = sin(g->angle);
	while (k < 6)
	{
		px = mn_x + (int)(dir_x * k);
		py = mn_y + (int)(dir_y * k);
		if (px >= 0 && px < MINMAP_WI && py >= 0 && py < MINMAP_HE)
		{
			dst = g->d_imag + (py * g->size_line + px * (g->bits_per_pixel
						/ 8));
			*(unsigned int *)dst = 0x000000;
		}
		k++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->imag, 5, 5);
}

void	help2_drow_minimap(t_game *g, int min_x, int min_y, int x)
{
	int		y;
	int		i;
	int		j;
	char	*dst;

	i = min_x;
	j = min_y;
	y = 0;
	while (j <= min_y + MINMAP_HE && j < g->i * MINTILE && y < MINMAP_HE)
	{
		i = min_x;
		x = 0;
		while (i <= min_x + MINMAP_WI && i < ftk_strlen(g->map[min_y / MINTILE])
			* MINTILE && x < MINMAP_WI)
		{
			dst = g->d_imag + (y * g->size_line + x * (g->bits_per_pixel / 8));
			help4_drow_minimap(g, dst, i, j);
			i++;
			x++;
		}
		y++;
		j++;
	}
}

void	help3_drow_minimap(t_game *g, int min_x, int min_y)
{
	double	mi_x;
	double	mi_y;

	help2_drow_minimap(g, min_x, min_y, 0);
	mi_x = g->player_x / TILE;
	mi_y = g->player_y / TILE;
	min_x = (int)(mi_x * MINTILE) - min_x;
	min_y = (int)(mi_y * MINTILE) - min_y;
	help_drow_minimap(g, min_x, min_y, NULL);
	help1_drow_minimap(g, min_x, min_y, NULL);
}

void	draw_minimap(t_game *g, int min_x, int min_y)
{
	if (min_x < 0 || min_y < 0)
	{
		if (min_x < 0)
			min_x = 0;
		if (min_y < 0)
			min_y = 0;
	}
	if ((min_y + MINMAP_HE) / MINTILE > g->i - 1
		|| (min_x + MINMAP_WI) / MINTILE > ftk_strlen(g->map[min_y / MINTILE]))
	{
		if ((min_y + MINMAP_HE) / MINTILE > g->i - 1)
		{
			if (MINMAP_HE < g->i * MINTILE)
				min_y -= (min_y + MINMAP_HE) - (g->i * MINTILE);
		}
		if ((min_x + MINMAP_WI) / MINTILE > ftk_strlen(g->map[min_y / MINTILE]))
		{
			if (MINMAP_WI < ftk_strlen(g->map[min_y / MINTILE]) * MINTILE)
				min_x -= (min_x + MINMAP_WI)
					- (ftk_strlen(g->map[min_y / MINTILE]) * MINTILE);
		}
	}
	help3_drow_minimap(g, min_x, min_y);
}
