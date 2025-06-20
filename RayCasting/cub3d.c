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

int is_wall(double x, double y, t_game **game, char m)
{
	int map_x = (int)(x / TILE);
	int map_y = (int)(y / TILE);
	(void)m;

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
		if ((*game)->map_section[map_y][map_x] == '1')
			break;
		xn += step_x;
		yn += step_y;
	}
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
		if ((*game)->map_section[map_y][map_x] == '1')
			break;
		xn += step_x;
		yn += step_y;
	}
	distance = sqrt(pow(xn - (*game)->player_x, 2) + pow(yn - (*game)->player_y, 2));
	(*game)->distances_y = distance;
}

double	dda(t_game **game)
{
	int i = 0;
	int		facing_down = ((*game)->ray_angle > 0 && (*game)->ray_angle < M_PI);
	int		facing_right = ((*game)->ray_angle < M_PI / 2 || (*game)->ray_angle > 3 * M_PI / 2);

	while ((*game)->map_section[i])
		i++;
	the_distance_with_y(game, i);
	the_distance_with_x(game, i);

	if ((*game)->distances_x > (*game)->distances_y)
	{
		if (facing_down)
			(*game)->char_color = 'h';
		else
			(*game)->char_color = 'K';
		return ((*game)->distances_y);
	}
	else
	{
		if (facing_right)
			(*game)->char_color = 'x';
		else
			(*game)->char_color = 'y';
		return ((*game)->distances_x);
	}
	return ((*game)->distances_y);
}

void move_player11(t_game **game, double angle_offset, char m)
{
    double nx = (*game)->player_x + cos((*game)->angle + angle_offset) * SPED;
    double ny = (*game)->player_y + sin((*game)->angle + angle_offset) * SPED;

    if (!is_wall(nx, ny, game, m) && ny > 60.0 && nx > 60.0)
    {
        (*game)->player_x = nx;
        (*game)->player_y = ny;
    }
}


int	update_position_player(t_game **game)
{
	if ((*game)->keys[65363])
		(*game)->angle += 0.04;
	if ((*game)->keys[65361])
		(*game)->angle -= 0.04;
	if ((*game)->keys[119]) // W
    	move_player11(game, 0, 'w');
	if ((*game)->keys[115]) // S
    	move_player11(game, M_PI, 's');
	if ((*game)->keys[100]) // D
    	move_player11(game, M_PI / 2, 'd');
	if ((*game)->keys[97]) // A
		move_player11(game, -M_PI / 2, 'a');
	return (0);
}

void draw_column(t_game **game, int x, double dist)
{
	// printf("dist %f\n", dist);
	int	color;
	int wall_height;
	double dis_projected_plan = (MAP_WIDTH / 2) / tan(FOV / 2);
	double corrected_dist = dist * cos((*game)->ray_angle - (*game)->angle);

	wall_height = (TILE / corrected_dist) * dis_projected_plan;
	if (wall_height > MAP_HEIGHT || dist == 0.0)
		wall_height = MAP_HEIGHT;
	int start = (MAP_HEIGHT / 2) - (wall_height / 2);
	int y = 0;

	if ((*game)->char_color == 'h')
		color = 0xC70039;
	else if ((*game)->char_color == 'k')
		color = 0xDAF7A6;
	else if ((*game)->char_color == 'x')
		color = 0xFFC300;
	else if ((*game)->char_color == 'y')
		color = 0xFF5733;
	while (y < start)
		mlx_pixel_put((*game)->mlx, (*game)->win, x, y++, 0xb0d2fa);
	while (y < start + wall_height)
		mlx_pixel_put((*game)->mlx, (*game)->win, x, y++, color);
	while (y < MAP_HEIGHT)
		mlx_pixel_put((*game)->mlx, (*game)->win, x, y++, 0x444444);
}

int raycasting(t_game **game)
{
	update_position_player(game);
	int x = 0;
	double step = FOV / MAP_WIDTH;
	(*game)->ray_angle = (*game)->angle - (FOV / 2);
	while (x < MAP_WIDTH)
	{
		printf("px %f py %f\n", (*game)->player_x, (*game)->player_y);
		normalize_angle(game);
		(*game)->dist = ceil(dda(game));
		draw_column(game, x, (*game)->dist);
		(*game)->ray_angle += step;
		x++;
	}
	// printf("hhh\n");
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
	return (0);
}

int	release_key(int key, t_game **game)
{
	(*game)->keys[key] = 0;
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

	(*game)->win = mlx_new_window((*game)->mlx, MAP_WIDTH, MAP_HEIGHT, "Cub3D");
	if (!(*game)->win)
	{
		ft_putstr_fd("Error creating window\n", 2);
		exit(1);
	}

	change_line_to_null(game);
	chose_the_angle_p(game);
	(*game)->player_x *= TILE;
	(*game)->player_y *= TILE;
	(*game)->player_x += TILE / 2;
	(*game)->player_y += TILE / 2;

	mlx_hook((*game)->win, 2, 1L << 0, prees_key, game);
	mlx_hook((*game)->win, 3, 1L << 1, release_key, game);
	mlx_loop_hook((*game)->mlx, raycasting, game);
	mlx_hook((*game)->win, 17, 0, mlx_loop_end, (*game)->mlx);
	mlx_loop((*game)->mlx);
}
