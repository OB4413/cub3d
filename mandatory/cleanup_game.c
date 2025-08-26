/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:44:01 by ynadime           #+#    #+#             */
/*   Updated: 2025/08/26 11:43:49 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cleanup_game(t_game *game)
{
	destroy_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_memory();
}

void	destroy_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->pst_imag)
			ft_destroy_image(game->mlx, game->pst_imag[i]);
		i++;
	}
	ft_destroy_image(game->mlx, game->imag_v);
	ft_destroy_image(game->mlx, game->n_image);
	ft_destroy_image(game->mlx, game->s_image);
	ft_destroy_image(game->mlx, game->e_image);
	ft_destroy_image(game->mlx, game->w_image);
}
