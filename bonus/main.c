/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:45:02 by ynadime           #+#    #+#             */
/*   Updated: 2025/08/25 15:31:19 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	clean_images(t_game *g)
{
	(void)g;
	//ft_malloc(0, free, g);
	exit(1);
}

void	ft_check_images(t_game *g)
{
	int x;

	x = 0;
	while (x < 4)
	{
		if (!g->ak_imag[x])
			clean_images(g);
		x++;
	}
	x = 0;
	while (x < 4)
	{
		if (!g->pst_imag[x])
			clean_images(g);
		x++;
	}
	x = 0;
	while (x < 4)
	{
		if (!g->mg_imag[x])
			clean_images(g);
		x++;
	}
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
	help_raycaster(game, 0);
	mlx_hook(game->win, 2, 1L << 0, prees_key, game);
	mlx_hook(game->win, 3, 1L << 1, release_key, game);
	mlx_hook(game->win, 5, 1L << 3, stop_gun, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_mouse_hook(game->win, shot_gun, game);
	mlx_loop_hook(game->mlx, raycasting, game);
	mlx_hook(game->win, 17, 0, mlx_loop_end, game->mlx);
	mlx_loop(game->mlx);
}

bool	is_valid_filename(char *filename)
{
	if (ft_strlen(filename) < 5 || ft_strncmp(&filename[ft_strlen(filename)]
			- 4, ".cub", 4) || !ft_strncmp(&filename[ft_strlen(filename)] - 5,
			"/.cub", 5))
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	game.mlx = mlx_init();
	if (ac != 2 || is_valid_filename(av[1]) == false)
		return (ft_putstr_fd("Error\nUsage: ./cub3D <mapfile.cub>\n", 2), 1);
	if (parse_file(av[1], &game))
		return (1);
	raycaster(&game);
}
