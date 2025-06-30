/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by obarais           #+#    #+#             */
/*   Updated: 2025/06/20 09:36:10 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_wall(double x, double y, t_game **game)
{
	int map_x = (int)(x / TILE);
	int map_y = (int)(y / TILE);

	if ((*game)->map_section[map_y][map_x] == 'D')
		return (1);
	if ((*game)->map_section[map_y][map_x] == 'C')
		return (0);
	if ((*game)->map_section[map_y][map_x] != '0' && (*game)->map_section[map_y][map_x] != (*game)->player_char)
		return (1);
	return ((*game)->map_section[map_y][map_x] == '1');
}

void normalize_angle(t_game **game)
{
	while ((*game)->ray_angle < 0)
		(*game)->ray_angle += 2 * M_PI;
	while ((*game)->ray_angle >= 2 * M_PI)
		(*game)->ray_angle -= 2 * M_PI;
}

int ftk_strlen(char *str)
{
	int i = 0;

	while (str && str[i])
		i++;
	return i;
}

void	the_distance_with_x(t_game **game, int i)
{
	double	xn, yn;
	int		map_x, map_y;
	double	step_x, step_y;
	double	distance;
	int		facing_right = ((*game)->ray_angle < M_PI / 2 || (*game)->ray_angle > 3 * M_PI / 2);
	int		facing_down = ((*game)->ray_angle > 0 && (*game)->ray_angle < M_PI);


	xn = floor((*game)->player_x / TILE) * TILE;
	if (facing_right)
		xn += TILE;

	yn = tan((*game)->ray_angle) * (xn - (*game)->player_x) + (*game)->player_y;

	step_x = TILE;
	if (!facing_right)
		step_x *= -1;

	step_y = step_x * tan((*game)->ray_angle);
	if ((!facing_down && step_y > 0) || (facing_down && step_y < 0))
		step_y *= -1;

	while (1)
	{
		map_x = (int)xn / TILE;
		map_y = (int)yn / TILE;
		if (!facing_right)
			map_x -= 1;
		if (map_y < 0 || map_y >= i || !(*game)->map_section[map_y])
			break;

		int fx = ftk_strlen((*game)->map_section[map_y]);
		if (map_x < 0 || map_x >= fx)
			break;
		if ((*game)->map_section[map_y][map_x] != '0' && (*game)->map_section[map_y][map_x] != 'C')
			break;
		xn += step_x;
		yn += step_y;
	}
	(*game)->xa = yn;
	(*game)->xb = xn;
	distance = sqrt(pow(xn - (*game)->player_x, 2) + pow(yn - (*game)->player_y, 2));
	(*game)->distances_x = distance;
}


void	the_distance_with_y(t_game **game, int i)
{
	double	xn, yn;
	int map_x, map_y;
	double	step_x, step_y;
	double	distance;
	int		facing_down = ((*game)->ray_angle > 0 && (*game)->ray_angle < M_PI);
	int		facing_right = ((*game)->ray_angle < M_PI / 2 || (*game)->ray_angle > 3 * M_PI / 2);

	yn = floor((*game)->player_y / TILE) * TILE;
	if (facing_down)
		yn += TILE;
	xn = (*game)->player_x + (yn - (*game)->player_y) / tan((*game)->ray_angle);

	step_y = TILE;
	if (!facing_down)
		step_y *= -1;

	step_x = step_y / tan((*game)->ray_angle);
	if ((!facing_right && step_x > 0) || (facing_right && step_x < 0))
		step_x *= -1;

	while (1)
	{
		map_x = (int)xn / TILE;
		map_y = (int)yn / TILE;
		if (!facing_down)
			map_y -= 1;
		if (map_y < 0 || map_y >= i || !(*game)->map_section[map_y])
			break;

		int fx = ftk_strlen((*game)->map_section[map_y]);
		if (map_x < 0 || map_x >= fx)
			break;
		if ((*game)->map_section[map_y][map_x] != '0' && (*game)->map_section[map_y][map_x] != 'C')
			break;
		xn += step_x;
		yn += step_y;
	}
	(*game)->ya = yn;
	(*game)->yb = xn;
	distance = sqrt(pow(xn - (*game)->player_x, 2) + pow(yn - (*game)->player_y, 2));
	(*game)->distances_y = distance;
}


int check_the_dor(t_game **g, double y, double x, int v)
{
	int	facing_down = ((*g)->ray_angle > 0 && (*g)->ray_angle < M_PI);
	int	facing_right = ((*g)->ray_angle < M_PI / 2 || (*g)->ray_angle > 3 * M_PI / 2);

	if (v)
	{
		if (!facing_right)
			x -= TILE;
	}
	else
	{
		if (!facing_down)
			y -= TILE;
	}
	int map_y = (int)(y / TILE);
	int map_x = (int)(x / TILE);
	if ((*g)->map_section[map_y][map_x] == 'D')
		return (1);
	return (0);
}


double	dda(t_game **game)
{
	int		facing_down = ((*game)->ray_angle > 0 && (*game)->ray_angle < M_PI);
	int		facing_right = ((*game)->ray_angle < M_PI / 2 || (*game)->ray_angle > 3 * M_PI / 2);

	the_distance_with_y(game, (*game)->i);
	the_distance_with_x(game, (*game)->i);

	if ((*game)->distances_x > (*game)->distances_y)
	{
		(*game)->x_or_y = 1;
		if (check_the_dor(game, (*game)->ya, (*game)->yb, 0))
			(*game)->char_color = 'd';
		else if (facing_down)
			(*game)->char_color = 'h';
		else
			(*game)->char_color = 'k';
		return ((*game)->distances_y);
	}
	else
	{
		(*game)->x_or_y = 0;
		if (check_the_dor(game, (*game)->xa, (*game)->xb, 1))
			(*game)->char_color = 'd';
		else if (facing_right)
			(*game)->char_color = 'x';
		else
			(*game)->char_color = 'y';
		return ((*game)->distances_x);
	}
	return ((*game)->distances_y);
}

void move_player11(t_game **game, double angle_offset)
{
    double nx = (*game)->player_x + cos((*game)->angle + angle_offset) * SPED;
    double ny = (*game)->player_y + sin((*game)->angle + angle_offset) * SPED;

    if (!is_wall(nx, ny, game) && ny > TILE && nx > TILE)
    {
        (*game)->player_x = nx;
        (*game)->player_y = ny;
    }
}

void open_and_close_door(t_game **g)
{
	int px = (int)((*g)->player_x + cos((*g)->angle) * TILE) / TILE;
	int py = (int)((*g)->player_y + sin((*g)->angle) * TILE) / TILE;

	if ((*g)->map_section[(int)(*g)->player_y / TILE][(int)(*g)->player_x / TILE] == 'C')
		return ;

	int dist_x = ((*g)->player_x / TILE) - px;
	int dist_y = ((*g)->player_y / TILE) - py;
	double dist = sqrt(dist_x * dist_x + dist_y * dist_y) * TILE;

	if ((*g)->map_section[py][px] == 'D' && dist <= TILE)
		(*g)->map_section[py][px] = 'C';
	else if ((*g)->map_section[py][px] == 'C' && dist <= 2 * TILE)
		(*g)->map_section[py][px] = 'D';
}

void	change_the_gane(t_game **g)
{
	(*g)->ng++;
	if ((*g)->ng == 3)
		(*g)->ng = 0;
}

int	update_position_player(t_game **game)
{
	int x, y;

	x = (*game)->player_x / TILE;
	y = (*game)->player_y / TILE;
	if ((*game)->keys[65363])
		(*game)->angle += SPED_RL;
	if ((*game)->keys[65361])
		(*game)->angle -= SPED_RL;
	if ((*game)->keys[119]) // W
    	move_player11(game, 0);
	if ((*game)->keys[115]) // S
    	move_player11(game, M_PI);
	if ((*game)->keys[100]) // D
    	move_player11(game, M_PI / 2);
	if ((*game)->keys[97]) // A
		move_player11(game, -M_PI / 2);

	if ((*game)->map_section[y][x] != 'C' && (*game)->map_section[y][x] != 'D')
	{
		(*game)->map_section[y][x] = '0';
		x = (*game)->player_x / TILE;
		y = (*game)->player_y / TILE;
		if ((*game)->map_section[y][x] != 'C' && (*game)->map_section[y][x] != 'D')
			(*game)->map_section[y][x] = (*game)->player_char;
	}
	return (0);
}

void	draw_minimap(t_game **g)
{
	int min_x = (*g)->player_x / TILE;
	int min_y = (*g)->player_y / TILE;

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
	if ((min_y + MINMAP_HE) / MINTILE > (*g)->i - 1 || (min_x + MINMAP_WI) / MINTILE > ftk_strlen((*g)->map_section[min_y/ MINTILE]))
	{
		if ((min_y + MINMAP_HE) / MINTILE > (*g)->i - 1)
		{
			if (MINMAP_HE < (*g)->i * MINTILE)
				min_y -= (min_y + MINMAP_HE) - ((*g)->i * MINTILE);
		}
		if ((min_x + MINMAP_WI) / MINTILE > ftk_strlen((*g)->map_section[min_y/ MINTILE]))
		{
			if (MINMAP_WI < ftk_strlen((*g)->map_section[min_y/ MINTILE]) * MINTILE)
				min_x -= (min_x + MINMAP_WI) - (ftk_strlen((*g)->map_section[min_y/ MINTILE]) * MINTILE);
		}
	}
	int i = min_x;
	int j = min_y;
	while (j <= min_y + MINMAP_HE && j < (*g)->i * MINTILE && y < MINMAP_HE)
	{
		i = min_x;
		x = 0;
		while (i <= min_x + MINMAP_WI && i < ftk_strlen((*g)->map_section[min_y/ MINTILE]) * MINTILE && x < MINMAP_WI)
		{
			char *dst = (*g)->d_imag + (y * (*g)->size_line + x * ((*g)->bits_per_pixel / 8));
			if ((*g)->map_section[j / MINTILE] && (*g)->map_section[j / MINTILE][i / MINTILE] == '1')
				*(unsigned int *)dst = 0xffffff;
			else if ((*g)->map_section[j / MINTILE] && ((*g)->map_section[j / MINTILE][i / MINTILE] == 'D' || (*g)->map_section[j / MINTILE][i / MINTILE] == 'C'))
				*(unsigned int *)dst = 0xffff00;
			else if ((*g)->map_section[j / MINTILE] && ((*g)->map_section[j / MINTILE][i / MINTILE] == '0' || (*g)->map_section[j / MINTILE][i / MINTILE] == (*g)->player_char))
				*(unsigned int *)dst = 0xff00ff;
			else
				*(unsigned int *)dst = 0x000000;
			i++;
			x++;
		}
		y++;
		j++;
	}

	double mi_x = (*g)->player_x / TILE;
	double mi_y = (*g)->player_y / TILE;
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
				char *dst = (*g)->d_imag + (py * (*g)->size_line + px * ((*g)->bits_per_pixel / 8));
				*(unsigned int *)dst = 0x000000;
			}
			dx++;
		}
		dy++;
	}

	double dir_x = cos((*g)->angle);
	double dir_y = sin((*g)->angle);
	int k = 0;
	while (k < 6)
	{
		px = mn_x + (int)(dir_x * k);
		py = mn_y + (int)(dir_y * k);
		if (px >= 0 && px < MINMAP_WI && py >= 0 && py < MINMAP_HE)
		{
			char *dst = (*g)->d_imag + (py * (*g)->size_line + px * ((*g)->bits_per_pixel / 8));
			*(unsigned int *)dst = 0x000000;
		}
		k++;
	}
	mlx_put_image_to_window((*g)->mlx, (*g)->win, (*g)->imag, 5, 5);
}

void draw_column(t_game **game, int x, double dist)
{
	int	color;
	char *dst;
	int wall_height;
	double dis_projected_plan = (WIN_WIDTH / 2) / tan(FOV / 2);
	double corrected_dist = dist * cos((*game)->ray_angle - (*game)->angle);

	wall_height = (TILE / corrected_dist) * dis_projected_plan;
	if (wall_height > WIN_HEIGHT || dist == 0.0)
		wall_height = WIN_HEIGHT;
	int start = (WIN_HEIGHT / 2) - (wall_height / 2);
	int y = 0;

	if ((*game)->char_color == 'h')
		color = 0xC70039;
	else if ((*game)->char_color == 'k')
		color = 0xDAF7A6;
	else if ((*game)->char_color == 'x')
		color = 0xFFC300;
	else if ((*game)->char_color == 'y')
		color = 0xFF5733;
	else if ((*game)->char_color == 'd')
		color = 0xFF00ad;
	while (y < start)
	{
		if ((y < 2 || y >= 8 + MINMAP_HE) || (x < 2 || x >= 8 + MINMAP_WI))
		{
			dst = (*game)->d_imag_v + (y * (*game)->sl + x *((*game)->bpp / 8));
			*(unsigned int *)dst = 0xb0d2fa;
		}
		y++;
	}
	while (y < start + wall_height)
	{
		if ((y < 2 || y >= 8 + MINMAP_HE) || (x < 2 || x >= 8 + MINMAP_WI))
		{
			dst = (*game)->d_imag_v + (y * (*game)->sl + x *((*game)->bpp / 8));
			*(unsigned int *)dst = color;
		}
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		if ((y < 2 || y > 8 + MINMAP_HE) || (x < 2 || x > 8 + MINMAP_WI))
		{
			dst = (*game)->d_imag_v + (y * (*game)->sl + x *((*game)->bpp / 8));
			*(unsigned int *)dst = 0x444444;
		}
		y++;
	}
}

void	drow_imag_player(t_game **g)
{
	int x, y;
	if ((*g)->ng == 0)
		(*g)->d_p_imag = mlx_get_data_addr((*g)->pst_imag[(*g)->h], &(*g)->pbpp, &(*g)->psl, &(*g)->pend);
	if ((*g)->ng == 1)
		(*g)->d_p_imag = mlx_get_data_addr((*g)->ak_imag[(*g)->h], &(*g)->pbpp, &(*g)->psl, &(*g)->pend);
	if ((*g)->ng == 2)
		(*g)->d_p_imag = mlx_get_data_addr((*g)->mg_imag[(*g)->h], &(*g)->pbpp, &(*g)->psl, &(*g)->pend);

	x = 0;
	y = 0;
	while (y <= WIN_HEIGHT)
	{
		x = 0;
		while (x <= WIN_WIDTH)
		{
			char *dst = (*g)->d_p_imag + (y * (*g)->psl + x * ((*g)->pbpp / 8));
			if (*(unsigned int *)dst != 0x01fefe)
			{
				char *st = (*g)->d_imag_v + (y * (*g)->sl + x * ((*g)->bpp / 8));
				*(unsigned int *)st = *(unsigned int *)dst;
			}
			x++;
		}
		y++;
	}
	if ((*g)->shot == 1)
	{
		(*g)->h++;
		if ((*g)->ng == 0)
		{
			if ((*g)->pst_imag[(*g)->h] == NULL)
				(*g)->h = 0;
		}
		if ((*g)->ng == 1)
		{
			if ((*g)->ak_imag[(*g)->h] == NULL)
				(*g)->h = 0;
		}
		if ((*g)->ng == 2)
		{
			if ((*g)->mg_imag[(*g)->h] == NULL)
				(*g)->h = 0;
		}
	}
}

int raycasting(t_game **game)
{
	mlx_clear_window((*game)->mlx, (*game)->win);
	update_position_player(game);
	int x = 0;
	double step = FOV / WIN_WIDTH;
	(*game)->ray_angle = (*game)->angle - (FOV / 2);
	while (x < WIN_WIDTH)
	{
		normalize_angle(game);
		(*game)->dist = ceil(dda(game));
		draw_column(game, x, (*game)->dist);
		(*game)->ray_angle += step;
		x++;
	}
	drow_imag_player(game);
	mlx_put_image_to_window((*game)->mlx, (*game)->win, (*game)->imag_v, 0, 0);
	draw_minimap(game);
	mlx_mouse_move((*game)->mlx, (*game)->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}

void chose_the_angle_p(t_game **game)
{
	if ((*game)->player_char == 'N')
		(*game)->angle = 3 * M_PI / 2;
	else if ((*game)->player_char == 'S')
		(*game)->angle = M_PI / 2;
	else if ((*game)->player_char == 'E')
		(*game)->angle = 0;
	else if ((*game)->player_char == 'W')
		(*game)->angle = M_PI;
}

void	change_line_to_null(t_game **game)
{
	int i = 0;
	int j = 0;

	while ((*game)->map_section[j])
	{
		i = 0;
		while ((*game)->map_section[j][i])
		{
			if ((*game)->map_section[j][i] == '\n')
				(*game)->map_section[j][i] = '\0';
			i++;
		}
		j++;
	}
}
int prees_key(int key, t_game **game)
{
	if (key == 65307)
		exit(0);
	(*game)->keys[key] = 1;
	if ((*game)->keys[101])
		open_and_close_door(game);
	if ((*game)->keys[121])
		change_the_gane(game);
	return (0);
}

int	release_key(int key, t_game **game)
{
	(*game)->keys[key] = 0;
	return (0);
}

int	mouse_move(int x, int y, t_game **g)
{
	(void)y;
	static int i = WIN_WIDTH / 2;
	int j;

	j = x - i;
	if (j > 0)
		(*g)->angle += j * SPED_RL / 2;
	else if (j < 0)
	{
		j *= -1;
		(*g)->angle -= j * SPED_RL / 2;
	}
	return (0);
}

void	init_imag_player(t_game **g)
{
	(*g)->pst_imag = malloc(sizeof(void *) * 5);
	(*g)->mg_imag = malloc(sizeof(void *) * 5);
	(*g)->ak_imag = malloc(sizeof(void *) * 5);
	int x, y;

	(*g)->pst_imag[0] = mlx_xpm_file_to_image((*g)->mlx, "textures/player/pistol/1.xpm", &x, &y);
	(*g)->pst_imag[1] = mlx_xpm_file_to_image((*g)->mlx, "textures/player/pistol/2.xpm", &x, &y);
	(*g)->pst_imag[2] = mlx_xpm_file_to_image((*g)->mlx, "textures/player/pistol/3.xpm", &x, &y);
	(*g)->pst_imag[3] = mlx_xpm_file_to_image((*g)->mlx, "textures/player/pistol/4.xpm", &x, &y);
	(*g)->pst_imag[4] = NULL;

	(*g)->mg_imag[0] = mlx_xpm_file_to_image((*g)->mlx, "textures/player/mg/1.xpm", &x, &y);
	(*g)->mg_imag[1] = mlx_xpm_file_to_image((*g)->mlx, "textures/player/mg/2.xpm", &x, &y);
	(*g)->mg_imag[2] = mlx_xpm_file_to_image((*g)->mlx, "textures/player/mg/3.xpm", &x, &y);
	(*g)->mg_imag[3] = mlx_xpm_file_to_image((*g)->mlx, "textures/player/mg/4.xpm", &x, &y);
	(*g)->mg_imag[4] = NULL;

	(*g)->ak_imag[0] = mlx_xpm_file_to_image((*g)->mlx, "textures/player/AK/1.xpm", &x, &y);
	(*g)->ak_imag[1] = mlx_xpm_file_to_image((*g)->mlx, "textures/player/AK/2.xpm", &x, &y);
	(*g)->ak_imag[2] = mlx_xpm_file_to_image((*g)->mlx, "textures/player/AK/3.xpm", &x, &y);
	(*g)->ak_imag[3] = mlx_xpm_file_to_image((*g)->mlx, "textures/player/AK/4.xpm", &x, &y);
	(*g)->ak_imag[4] = NULL;

	(*g)->ng = 0;
	(*g)->shot = 0;
	(*g)->h = 0;
}

int	shot_gun(int butom, int x, int y, t_game **game)
{
	(void)x;
	(void)y;

	if (butom == 1)
		(*game)->shot = 1;
	return (0);
}

int	stop_gun(int butom, int x, int y, t_game **game)
{
	(void)x;
	(void)y;

	if (butom == 1)
	{
		(*game)->shot = 0;
		(*game)->h = 0;
	}
	return (0);
}

void raycaster(t_game **game)
{
	(*game)->mlx = mlx_init();
	if (!(*game)->mlx)
	{
		ft_putstr_fd("Error initializing MLX\n", 2);
		exit(1);
	}

	(*game)->win = mlx_new_window((*game)->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!(*game)->win)
	{
		ft_putstr_fd("Error creating window\n", 2);
		exit(1);
	}

	(*game)->i = 0;
	while ((*game)->map_section[(*game)->i])
		(*game)->i++;

	change_line_to_null(game);
	chose_the_angle_p(game);
	(*game)->player_x *= TILE;
	(*game)->player_y *= TILE;
	(*game)->player_x += TILE / 2;
	(*game)->player_y += TILE / 2;
	(*game)->imag = mlx_new_image((*game)->mlx, MINMAP_WI, MINMAP_HE);
	(*game)->d_imag = mlx_get_data_addr((*game)->imag, &(*game)->bits_per_pixel, &(*game)->size_line, &(*game)->endian);
	(*game)->imag_v = mlx_new_image((*game)->mlx, WIN_WIDTH, WIN_HEIGHT);
	(*game)->d_imag_v = mlx_get_data_addr((*game)->imag_v, &(*game)->bpp, &(*game)->sl, &(*game)->en);
	init_imag_player(game);


	mlx_hook((*game)->win, 2, 1L << 0, prees_key, game);
	mlx_hook((*game)->win, 3, 1L << 1, release_key, game);
	mlx_hook((*game)->win, 5, 1L << 3, stop_gun, game);
	mlx_hook((*game)->win, 6, 1L << 6, mouse_move, game);
	mlx_mouse_hook((*game)->win, shot_gun, game);
	mlx_loop_hook((*game)->mlx, raycasting, game);
	mlx_hook((*game)->win, 17, 0, mlx_loop_end, (*game)->mlx);
	mlx_loop((*game)->mlx);
}
