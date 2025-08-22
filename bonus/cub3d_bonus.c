/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by obarais           #+#    #+#             */
/*   Updated: 2025/08/21 12:21:19 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	help_raycasting(t_game *game, int x)
{
	while (x < WIN_WIDTH)
	{
		normalize_angle(game);
		game->dist = ceil(dda(game));
		draw_view(game, x, game->dist, 0);
		game->ray_angle += FOV / WIN_WIDTH;
		x++;
	}
	drow_imag_player(game, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->imag_v, 0, 0);
	draw_minimap(game);
	mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

int	raycasting(t_game *game)
{
	if (game->ng == 4)
	{
		loop_chose_gun(game, 0, 0);
		return (0);
	}
	mlx_clear_window(game->mlx, game->win);
	update_position_player(game, 0, 0);
	if (game->index_jumb == 1 && game->jump < WIN_HEIGHT / 2 + 100)
		game->jump += 2;
	else if (game->jump > WIN_HEIGHT / 2)
	{
		game->index_jumb = 0;
		game->jump -= 2;
	}
	game->ray_angle = game->angle - (FOV / 2);
	help_raycasting(game, 0);
	return (0);
}

void	help_init_imag_player(t_game *g, int x, int y)
{
	g->mg_imag[2] = mlx_xpm_file_to_image(g->mlx, "textures/player/mg/3.xpm",
			&x, &y);
	g->mg_imag[3] = mlx_xpm_file_to_image(g->mlx, "textures/player/mg/4.xpm",
			&x, &y);
	g->mg_imag[4] = NULL;
	g->ak_imag[0] = mlx_xpm_file_to_image(g->mlx, "textures/player/AK/1.xpm",
			&x, &y);
	g->ak_imag[1] = mlx_xpm_file_to_image(g->mlx, "textures/player/AK/2.xpm",
			&x, &y);
	g->ak_imag[2] = mlx_xpm_file_to_image(g->mlx, "textures/player/AK/3.xpm",
			&x, &y);
	g->ak_imag[3] = mlx_xpm_file_to_image(g->mlx, "textures/player/AK/4.xpm",
			&x, &y);
	g->ak_imag[4] = NULL;
	g->n_image = mlx_xpm_file_to_image(g->mlx, "textures/N.xpm", &g->xn,
			&g->yn);
	g->s_image = mlx_xpm_file_to_image(g->mlx, "textures/S.xpm", &g->xs,
			&g->ys);
	g->e_image = mlx_xpm_file_to_image(g->mlx, "textures/E.xpm", &g->xe,
			&g->ye);
	g->w_image = mlx_xpm_file_to_image(g->mlx, "textures/W.xpm", &g->xw,
			&g->yw);
	g->door_imag = mlx_xpm_file_to_image(g->mlx, "textures/door.xpm", &g->xd,
			&g->yd);
}

void	init_imag_player(t_game *g, int x, int y)
{
	g->pst_imag = malloc(sizeof(void *) * 5);
	g->mg_imag = malloc(sizeof(void *) * 5);
	g->ak_imag = malloc(sizeof(void *) * 5);
	g->pst_imag[0] = mlx_xpm_file_to_image(g->mlx,
			"textures/player/pistol/1.xpm", &x, &y);
	g->pst_imag[1] = mlx_xpm_file_to_image(g->mlx,
			"textures/player/pistol/2.xpm", &x, &y);
	g->pst_imag[2] = mlx_xpm_file_to_image(g->mlx,
			"textures/player/pistol/3.xpm", &x, &y);
	g->pst_imag[3] = mlx_xpm_file_to_image(g->mlx,
			"textures/player/pistol/4.xpm", &x, &y);
	g->pst_imag[4] = NULL;
	g->mg_imag[0] = mlx_xpm_file_to_image(g->mlx, "textures/player/mg/1.xpm",
			&x, &y);
	g->mg_imag[1] = mlx_xpm_file_to_image(g->mlx, "textures/player/mg/2.xpm",
			&x, &y);
	help_init_imag_player(g, 0, 0);
	g->ng = 4;
	g->shot = 0;
	g->h = 0;
	g->index_jumb = 0;
	g->jump = WIN_HEIGHT / 2;
}

void	raycaster(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error initializing MLX\n", 2);
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game->win)
	{
		ft_putstr_fd("Error creating window\n", 2);
		exit(1);
	}
	game->i = 0;
	help_raycaster(game);
	mlx_hook(game->win, 2, 1L << 0, prees_key, game);
	mlx_hook(game->win, 3, 1L << 1, release_key, game);
	mlx_hook(game->win, 5, 1L << 3, stop_gun, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_mouse_hook(game->win, shot_gun, game);
	mlx_loop_hook(game->mlx, raycasting, game);
	mlx_hook(game->win, 17, 0, mlx_loop_end, game->mlx);
	mlx_loop(game->mlx);
}
