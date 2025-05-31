/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_section2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/05 11:18:22 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_up_map(t_game *game)
{
	int	i;
	int	len;
	int	map_idx;

	len = 0;
	map_idx = game->map_start_index;
	while (game->map[map_idx + len] != NULL)
		len++;
	while (len > 0 && is_empty_line(game->map[map_idx + len - 1]))
		len--;
	i = 0;
	game->map_section = ft_malloc(sizeof(char *) * (len + 1), FT_ALLOC);
	game->map_copy = ft_malloc(sizeof(char *) * (len + 1), FT_ALLOC);
	while (i < len)
	{
		game->map_section[i] = ft_malloc(
				ft_strlen(game->map[map_idx + i]) + 1, FT_ALLOC);
		ft_strlcpy(game->map_section[i], game->map[map_idx + i],
			ft_strlen(game->map[map_idx + i]) + 1);
		i++;
	}
	game->map_section[i] = NULL;
}

void	flood_fill(char **map, int y, int x)
{
	char	c;

	if (y < 0 || x < 0 || map[y] == NULL || x >= (int)ft_strlen(map[y]))
		handle_init_errors(6);
	c = map[y][x];
	if (c == '1' || c == 'V')
		return ;
	else if (c == 'X' || c == '\0')
		handle_init_errors(6);
	else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		map[y][x] = 'V';
	flood_fill(map, y - 1, x);
	flood_fill(map, y + 1, x);
	flood_fill(map, y, x - 1);
	flood_fill(map, y, x + 1);
}

void	set_player_direction_vector(t_game *game)
{
	if (game->player_char == 'N')
	{
		game->dir_x = 0;
		game->dir_y = -1;
	}
	else if (game->player_char == 'S')
	{
		game->dir_x = 0;
		game->dir_y = 1;
	}
	else if (game->player_char == 'E')
	{
		game->dir_x = 1;
		game->dir_y = 0;
	}
	else if (game->player_char == 'W')
	{
		game->dir_x = -1;
		game->dir_y = 0;
	}
}

void	set_player_camera_plane(t_game *game)
{
	if (game->player_char == 'N')
	{
		game->plane_x = 0.66;
		game->plane_y = 0;
	}
	else if (game->player_char == 'S')
	{
		game->plane_x = -0.66;
		game->plane_y = 0;
	}
	else if (game->player_char == 'E')
	{
		game->plane_x = 0;
		game->plane_y = 0.66;
	}
	else if (game->player_char == 'W')
	{
		game->plane_x = 0;
		game->plane_y = -0.66;
	}
}

void	set_player_direction(t_game *game)
{
	set_player_direction_vector(game);
	set_player_camera_plane(game);
}
