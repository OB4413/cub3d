/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_imag_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:05:33 by obarais           #+#    #+#             */
/*   Updated: 2025/08/21 12:19:25 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	drow_imag_in(t_game *g, int x, int *y, int start)
{
	int		scling;
	int		i;
	double	j;
	char	*im;
	char	*dst;

	scling = g->imag_width / TILE;
	i = round(g->ofs_tex) * scling;
	j = 0.0;
	while (*y <= start + g->wall_height && *y <= WIN_HEIGHT)
	{
		j = ((double)g->imag_height / g->wall_height) * (*y - start);
		if (j <= g->imag_height)
			dst = g->d_nsew + ((int)j * g->psl + i * (g->pbpp / 8));
		if (g->ng == 5 || (*y < 2 || *y >= 8 + MINMAP_HE) || (x < 2 || x >= 8
				+ MINMAP_WI))
		{
			if (*y <= WIN_HEIGHT)
			{
				im = g->d_imag_v + ((*y) * g->sl + x * (g->bpp / 8));
				*(unsigned int *)im = *(unsigned int *)dst;
			}
		}
		(*y)++;
	}
}

void	help_chose_the_image(t_game *g)
{
	if (g->char_color == 'w')
	{
		g->imag_height = g->yw;
		g->imag_width = g->xw;
		g->d_nsew = mlx_get_data_addr(g->w_image, &g->pbpp, &g->psl, &g->pend);
	}
	else if (g->char_color == 'd')
	{
		g->imag_height = g->yd;
		g->imag_width = g->xd;
		g->d_nsew = mlx_get_data_addr(g->door_imag, &g->pbpp, &g->psl,
				&g->pend);
	}
}

void	chose_the_image(t_game *g)
{
	if (g->char_color == 'n')
	{
		g->imag_height = g->yn;
		g->imag_width = g->xn;
		g->d_nsew = mlx_get_data_addr(g->n_image, &g->pbpp, &g->psl, &g->pend);
	}
	else if (g->char_color == 's')
	{
		g->imag_height = g->ys;
		g->imag_width = g->xs;
		g->d_nsew = mlx_get_data_addr(g->s_image, &g->pbpp, &g->psl, &g->pend);
	}
	else if (g->char_color == 'e')
	{
		g->imag_height = g->ye;
		g->imag_width = g->xe;
		g->d_nsew = mlx_get_data_addr(g->e_image, &g->pbpp, &g->psl, &g->pend);
	}
	else
		help_chose_the_image(g);
}

double	calcul_wall_height(t_game *g, double dist)
{
	double	dis_projected_plan;
	double	corrected_dist;
	int		wall_height;

	dis_projected_plan = (WIN_WIDTH / 2) / tan(FOV / 2);
	corrected_dist = dist * cos(g->ray_angle - g->angle);
	wall_height = (TILE / corrected_dist) * dis_projected_plan;
	return (wall_height);
}

void	draw_view(t_game *game, int x, double dist, int y)
{
	char	*dst;
	int		start;

	game->wall_height = calcul_wall_height(game, dist);
	start = game->jump - (game->wall_height / 2);
	chose_the_image(game);
	while (y < start)
	{
		if ((y < 2 || y >= 8 + MINMAP_HE) || (x < 2 || x >= 8 + MINMAP_WI))
		{
			dst = game->d_imag_v + (y * game->sl + x * (game->bpp / 8));
			*(unsigned int *)dst = game->ceiling_color;
		}
		y++;
	}
	drow_imag_in(game, x, &y, start);
	while (y < WIN_HEIGHT)
	{
		if ((y < 2 || y > 8 + MINMAP_HE) || (x < 2 || x > 8 + MINMAP_WI))
		{
			dst = game->d_imag_v + (y * game->sl + x * (game->bpp / 8));
			*(unsigned int *)dst = game->floor_color;
		}
		y++;
	}
}
