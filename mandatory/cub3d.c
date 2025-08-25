/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by obarais           #+#    #+#             */
/*   Updated: 2025/08/25 15:29:07 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	normalize_angle(t_game *game)
{
	while (game->ray_angle < 0)
		game->ray_angle += 2 * M_PI;
	while (game->ray_angle >= 2 * M_PI)
		game->ray_angle -= 2 * M_PI;
}

int	raycasting(t_game *game)
{
	int		x;
	double	step;

	mlx_clear_window(game->mlx, game->win);
	update_position_player(game);
	x = 0;
	step = FOV / WIN_WIDTH;
	game->ray_angle = game->angle - (FOV / 2);
	while (x < WIN_WIDTH)
	{
		normalize_angle(game);
		game->dist = ceil(dda(game, 0, 0));
		draw_view(game, x, game->dist, NULL);
		game->ray_angle += step;
		x++;
	}
	drow_imag_player(game, 0, 0, NULL);
	mlx_put_image_to_window(game->mlx, game->win, game->imag_v, 0, 0);
	return (0);
}

void	change_line_to_null(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[j])
	{
		i = 0;
		while (game->map[j][i])
		{
			if (game->map[j][i] == '\n')
				game->map[j][i] = '\0';
			i++;
		}
		j++;
	}
}

void	help_raycaster(t_game *game)
{
	change_line_to_null(game);
	chose_the_angle_p(game);
	game->player_x *= TILE;
	game->player_y *= TILE;
	game->player_x += TILE / 2;
	game->player_y += TILE / 2;
	game->imag_v = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->imag_v)
	{
		//ft_malloc(0, free, game);
		exit(1);
	}
	game->d_imag_v = mlx_get_data_addr(game->imag_v, &game->bpp, &game->sl,
			&game->en);
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
	while (game->map[game->i])
		game->i++;
	help_raycaster(game);
	init_imag_player(game, 0);
	mlx_hook(game->win, 2, 1L << 0, prees_key, game);
	mlx_hook(game->win, 3, 1L << 1, release_key, game);
	mlx_loop_hook(game->mlx, raycasting, game);
	mlx_hook(game->win, 17, 0, mlx_loop_end, game->mlx);
	mlx_loop(game->mlx);
}
