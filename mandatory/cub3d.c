/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by obarais           #+#    #+#             */
/*   Updated: 2025/08/04 21:48:51 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

int is_wall(double x, double y, t_game *game)
{
	int map_x = (int)(x / TILE);
	int map_y = (int)(y / TILE);

	return (game->map[map_y][map_x] == '1');
}

void normalize_angle(t_game *game)
{
	while (game->ray_angle < 0)
		game->ray_angle += 2 * M_PI;
	while (game->ray_angle >= 2 * M_PI)
		game->ray_angle -= 2 * M_PI;
}

int ftk_strlen(char *str)
{
	int i = 0;

	while (str && str[i])
		i++;
	return i;
}

void	the_distance_with_x(t_game *game, int i)
{
	double	xn, yn;
	int		map_x, map_y;
	double	step_x, step_y;
	double	distance;
	int		facing_right = (game->ray_angle < M_PI / 2 || game->ray_angle > 3 * M_PI / 2);
	int		facing_down = (game->ray_angle > 0 && game->ray_angle < M_PI);


	xn = floor(game->player_x / TILE) * TILE;
	if (facing_right)
		xn += TILE;

	yn = tan(game->ray_angle) * (xn - game->player_x) + game->player_y;

	step_x = TILE;
	if (!facing_right)
		step_x *= -1;

	step_y = step_x * tan(game->ray_angle);
	if ((!facing_down && step_y > 0) || (facing_down && step_y < 0))
		step_y *= -1;

	while (1)
	{
		map_x = (int)xn / TILE;
		map_y = (int)yn / TILE;
		if (!facing_right)
			map_x -= 1;
		if (map_y < 0 || map_y >= i || !game->map[map_y])
			break;

		int fx = ftk_strlen(game->map[map_y]);
		if (map_x < 0 || map_x >= fx)
			break;
		if (game->map[map_y][map_x] == '1')
			break;
		xn += step_x;
		yn += step_y;
	}
	game->xa = yn;
	game->xb = xn;
	distance = sqrt(pow(xn - game->player_x, 2) + pow(yn - game->player_y, 2));
	game->distances_x = distance;
}


void	the_distance_with_y(t_game *game, int i)
{
	double	xn, yn;
	int map_x, map_y;
	double	step_x, step_y;
	double	distance;
	int		facing_down = (game->ray_angle > 0 && game->ray_angle < M_PI);
	int		facing_right = (game->ray_angle < M_PI / 2 || game->ray_angle > 3 * M_PI / 2);

	yn = floor(game->player_y / TILE) * TILE;
	if (facing_down)
		yn += TILE;
	xn = game->player_x + (yn - game->player_y) / tan(game->ray_angle);

	step_y = TILE;
	if (!facing_down)
		step_y *= -1;

	step_x = step_y / tan(game->ray_angle);
	if ((!facing_right && step_x > 0) || (facing_right && step_x < 0))
		step_x *= -1;

	while (1)
	{
		map_x = (int)xn / TILE;
		map_y = (int)yn / TILE;
		if (!facing_down)
			map_y -= 1;
		if (map_y < 0 || map_y >= i || !game->map[map_y])
			break;

		int fx = ftk_strlen(game->map[map_y]);
		if (map_x < 0 || map_x >= fx)
			break;
		if (game->map[map_y][map_x] == '1')
			break;
		xn += step_x;
		yn += step_y;
	}
	game->ya = yn;
	game->yb = xn;
	distance = sqrt(pow(xn - game->player_x, 2) + pow(yn - game->player_y, 2));
	game->distances_y = distance;
}

double	dda(t_game *game)
{
	int		facing_down = (game->ray_angle > 0 && game->ray_angle < M_PI);
	int		facing_right = (game->ray_angle < M_PI / 2 || game->ray_angle > 3 * M_PI / 2);

	the_distance_with_y(game, game->i);
	the_distance_with_x(game, game->i);

	if (game->distances_x > game->distances_y)
	{
		game->ofs_tex = fmod(game->yb, (double)TILE);
		if (facing_down)
			game->char_color = 'n';
		else
			game->char_color = 's';
		return (game->distances_y);
	}
	else
	{
		game->ofs_tex = fmod(game->xa, (double)TILE);
		if (facing_right)
			game->char_color = 'w';
		else
			game->char_color = 'e';
		return (game->distances_x);
	}
	return (game->distances_y);
}

void move_player11(t_game *game, double angle_offset)
{
    double nx = game->player_x + cos(game->angle + angle_offset) * SPED;
    double ny = game->player_y + sin(game->angle + angle_offset) * SPED;

    if (!is_wall(nx, ny, game) && ny > TILE && nx > TILE)
    {
        game->player_x = nx;
        game->player_y = ny;
    }
}

int	shot_gun(t_game *game)
{
	game->shot = 1;
	return (0);
}

int	stop_gun(t_game *game)
{
	game->shot = 0;
	game->h = 0;
	return (0);
}

int	update_position_player(t_game *game)
{
	int x, y;

	x = game->player_x / TILE;
	y = game->player_y / TILE;
	if (game->keys[65363])
		game->angle += SPED_RL;
	if (game->keys[65361])
		game->angle -= SPED_RL;
	if (game->keys[119]) // W
    	move_player11(game, 0);
	if (game->keys[115]) // S
    	move_player11(game, M_PI);
	if (game->keys[100]) // D
    	move_player11(game, M_PI / 2);
	if (game->keys[97]) // A
		move_player11(game, -M_PI / 2);

	game->map[y][x] = '0';
	x = game->player_x / TILE;
	y = game->player_y / TILE;
	game->map[y][x] = game->player_char;
	return (0);
}

void draw_image(t_game *game, int x, double dist)
{
	char *dst;
	int wall_height;
	double dis_projected_plan = (WIN_WIDTH / 2) / tan(FOV / 2);
	double corrected_dist = dist * cos(game->ray_angle - game->angle);

	wall_height = (TILE / corrected_dist) * dis_projected_plan;
	if (wall_height > WIN_HEIGHT || dist == 0.0)
		wall_height = WIN_HEIGHT;
	int start = (WIN_HEIGHT / 2) - (wall_height / 2);
	int y = 0;

	if (!game->s_image)
		printf("hhhhhhhhhh\n");
	game->wall_height = wall_height;
	if (game->char_color == 'n')
	{
		game->imag_height = game->yn;
		game->imag_width = game->xn;
		game->d_nsew = mlx_get_data_addr(game->n_image, &game->pbpp, &game->psl, &game->pend);
	}
	else if (game->char_color == 's')
	{
		game->imag_height = game->ys;
		game->imag_width = game->xs;
		game->d_nsew = mlx_get_data_addr(game->s_image, &game->pbpp, &game->psl, &game->pend);
	}
	else if (game->char_color == 'e')
	{
		game->imag_height = game->ye;
		game->imag_width = game->xe;
		game->d_nsew = mlx_get_data_addr(game->e_image, &game->pbpp, &game->psl, &game->pend);
	}
	else if (game->char_color == 'w')
	{
		game->imag_height = game->yw;
		game->imag_width = game->xw;
		game->d_nsew = mlx_get_data_addr(game->w_image, &game->pbpp, &game->psl, &game->pend);
	}
	while (y < start)
	{
		dst = game->d_imag_v + (y++ * game->sl + x *(game->bpp / 8));
		*(unsigned int *)dst = 0xb0d2fa;
	}
	drow_imag_in(game, x, &y, start);
	while (y < WIN_HEIGHT)
	{
		dst = game->d_imag_v + (y++ * game->sl + x *(game->bpp / 8));
		*(unsigned int *)dst = 0x444444;
	}
}

void	drow_imag_player(t_game *g)
{
	int x, y;
	g->d_p_imag = mlx_get_data_addr(g->pst_imag[g->h], &g->pbpp, &g->psl, &g->pend);

	x = 0;
	y = 0;
	while (y <= WIN_HEIGHT)
	{
		x = 0;
		while (x <= WIN_WIDTH)
		{
			char *dst = g->d_p_imag + (y * g->psl + x * (g->pbpp / 8));
			if (*(unsigned int *)dst != 0x01fefe)
			{
				char *st = g->d_imag_v + (y * g->sl + x * (g->bpp / 8));
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

int raycasting(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	update_position_player(game);
	int x = 0;
	double step = FOV / WIN_WIDTH;
	game->ray_angle = game->angle - (FOV / 2);
	while (x < WIN_WIDTH)
	{
		normalize_angle(game);
		game->dist = ceil(dda(game));
		draw_image(game, x, game->dist);
		game->ray_angle += step;
		x++;
	}
	drow_imag_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->imag_v, 0, 0);
	return (0);
}

void chose_the_angle_p(t_game *game)
{
	if (game->player_char == 'N')
		game->angle = 3 * M_PI / 2;
	else if (game->player_char == 'S')
		game->angle = M_PI / 2;
	else if (game->player_char == 'E')
		game->angle = 0;
	else if (game->player_char == 'W')
		game->angle = M_PI;
}

void	change_line_to_null(t_game *game)
{
	int i = 0;
	int j = 0;

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
int prees_key(int key, t_game *game)
{
	if (key == 65307)
		exit(0);
	game->keys[key] = 1;
	if (game->keys[32])
		shot_gun(game);
	return (0);
}

int	release_key(int key, t_game *game)
{
	game->keys[key] = 0;
	if (!game->keys[32])
		stop_gun(game);
	return (0);
}

void	init_imag_player(t_game *g)
{
	g->pst_imag = malloc(sizeof(void *) * 5);
	g->mg_imag = malloc(sizeof(void *) * 5);
	g->ak_imag = malloc(sizeof(void *) * 5);
	int x, y;

	g->pst_imag[0] = mlx_xpm_file_to_image(g->mlx, "textures/player/pistol/1.xpm", &x, &y);
	g->pst_imag[1] = mlx_xpm_file_to_image(g->mlx, "textures/player/pistol/2.xpm", &x, &y);
	g->pst_imag[2] = mlx_xpm_file_to_image(g->mlx, "textures/player/pistol/3.xpm", &x, &y);
	g->pst_imag[3] = mlx_xpm_file_to_image(g->mlx, "textures/player/pistol/4.xpm", &x, &y);
	g->pst_imag[4] = NULL;

	g->n_image = mlx_xpm_file_to_image(g->mlx, g->no, &g->xn, &g->yn);
	g->s_image = mlx_xpm_file_to_image(g->mlx, g->so, &g->xs, &g->ys);
	g->e_image = mlx_xpm_file_to_image(g->mlx, g->ea, &g->xe, &g->ye);
	g->w_image = mlx_xpm_file_to_image(g->mlx, g->we, &g->xw, &g->yw);

	g->shot = 0;
	g->ng = 5;
	g->h = 0;
}


void raycaster(t_game *game)
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

	change_line_to_null(game);
	chose_the_angle_p(game);
	game->player_x *= TILE;
	game->player_y *= TILE;
	game->player_x += TILE / 2;
	game->player_y += TILE / 2;
	game->imag_v = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->d_imag_v = mlx_get_data_addr(game->imag_v, &game->bpp, &game->sl, &game->en);
	init_imag_player(game);

	mlx_hook(game->win, 2, 1L << 0, prees_key, game);
	mlx_hook(game->win, 3, 1L << 1, release_key, game);
	mlx_loop_hook(game->mlx, raycasting, game);
	mlx_hook(game->win, 17, 0, mlx_loop_end, game->mlx);
	mlx_loop(game->mlx);
}
