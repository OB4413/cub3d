/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:19:46 by obarais           #+#    #+#             */
/*   Updated: 2025/08/27 20:44:25 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	stop_gun(int butom, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (butom == 1)
	{
		game->shot = 0;
		game->h = 0;
	}
	return (0);
}

int	shot_gun(int butom, int x, int y, t_game *game)
{
	if (game->ng == 4)
	{
		if (butom == 1)
		{
			if (y >= 428)
			{
				if (x >= 700)
					game->ng = 0;
				else if (x >= 285)
					game->ng = 1;
				else if (x >= 0)
					game->ng = 2;
			}
		}
		return (0);
	}
	if (butom == 1)
		game->shot = 1;
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

int	mouse_move(int x, int y, t_game *g)
{
	static int	i = WIN_WIDTH / 2;
	int			j;

	(void)y;
	j = x - i;
	if (j > 0)
		g->angle += j * SPED_RL / 2;
	else if (j < 0)
	{
		j *= -1;
		g->angle -= j * SPED_RL / 2;
	}
	return (0);
}

int	loop_chose_gun(t_game *g, int x, int y)
{
	static int	i = 0;
	static void	*ch_gu = NULL;
	char		*file;

	file = ft_strjoin("textures/chose_gun/", ft_strjoin(ft_itoa(i), ".xpm"));
	ch_gu = mlx_xpm_file_to_image(g->mlx, file, &x, &y);
	if (!ch_gu)
	{
		cleanup_game(g);
		exit(1);
	}
	mlx_clear_window(g->mlx, g->win);
	mlx_put_image_to_window(g->mlx, g->win, ch_gu, 0, 0);
	mlx_string_put(g->mlx, g->win, 420, 450, 0xff0f, "Choose a gun");
	mlx_string_put(g->mlx, g->win, 421, 450, 0xff0f, "Choose a gun");
	usleep(180000);
	if (i == 13)
		i = 0;
	i++;
	mlx_destroy_image(g->mlx, ch_gu);
	return (0);
}
