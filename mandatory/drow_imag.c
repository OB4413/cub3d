/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_imag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:05:33 by obarais           #+#    #+#             */
/*   Updated: 2025/08/25 15:29:20 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	else if (g->char_color == 'w')
	{
		g->imag_height = g->yw;
		g->imag_width = g->xw;
		g->d_nsew = mlx_get_data_addr(g->w_image, &g->pbpp, &g->psl, &g->pend);
	}
}

void	draw_view(t_game *game, int x, double dist, char *dst)
{
	int		wall_height;
	double	dis_projected_plan;
	double	corrected_dist;
	int		start;
	int		y;

	dis_projected_plan = (WIN_WIDTH / 2) / tan(FOV / 2);
	corrected_dist = dist * cos(game->ray_angle - game->angle);
	wall_height = (TILE / corrected_dist) * dis_projected_plan;
	start = (WIN_HEIGHT / 2) - (wall_height / 2);
	y = 0;
	game->wall_height = wall_height;
	chose_the_image(game);
	while (y < start)
	{
		dst = game->d_imag_v + ((y++) * game->sl + x * (game->bpp / 8));
		*(unsigned int *)dst = game->ceiling_color;
	}
	drow_imag_in(game, x, &y, start);
	while (y < WIN_HEIGHT)
	{
		dst = game->d_imag_v + ((y++) * game->sl + x * (game->bpp / 8));
		*(unsigned int *)dst = game->floor_color;
	}
}

void	drow_imag_in(t_game *g, int x, int *y, int start)
{
	double	j;
	char	*im;
	char	*dst;
	int		scling;
	int		i;

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

void	drow_imag_player(t_game *g, int x, int y, char *st)
{
	char	*dst;

	g->d_p_imag = mlx_get_data_addr(g->pst_imag[g->h], &g->pbpp, &g->psl,
			&g->pend);
	while (y <= WIN_HEIGHT)
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
		y++;
	}
	if (g->shot == 1)
	{
		g->h++;
		if (g->pst_imag[g->h] == NULL)
			g->h = 0;
	}
}

void	init_imag_player(t_game *g, int x)
{
	int	y;

	g->pst_imag = malloc(sizeof(void *) * 5);
	g->pst_imag[0] = mlx_xpm_file_to_image(g->mlx,
			"textures/player/pistol/1.xpm", &x, &y);
	g->pst_imag[1] = mlx_xpm_file_to_image(g->mlx,
			"textures/player/pistol/2.xpm", &x, &y);
	g->pst_imag[2] = mlx_xpm_file_to_image(g->mlx,
			"textures/player/pistol/3.xpm", &x, &y);
	g->pst_imag[3] = mlx_xpm_file_to_image(g->mlx,
			"textures/player/pistol/4.xpm", &x, &y);
	g->pst_imag[4] = NULL;
	g->n_image = mlx_xpm_file_to_image(g->mlx, g->no, &g->xn, &g->yn);
	g->s_image = mlx_xpm_file_to_image(g->mlx, g->so, &g->xs, &g->ys);
	g->e_image = mlx_xpm_file_to_image(g->mlx, g->ea, &g->xe, &g->ye);
	g->w_image = mlx_xpm_file_to_image(g->mlx, g->we, &g->xw, &g->yw);
	if (!g->pst_imag[0] || !g->pst_imag[1] || !g->pst_imag[2] || !g->pst_imag[3])
	{
		//ft_malloc(0, free, g);
		exit(1);
	}
	g->shot = 0;
	g->ng = 5;
	g->h = 0;
}
