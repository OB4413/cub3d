/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:44:11 by ynadime           #+#    #+#             */
/*   Updated: 2025/08/24 15:44:12 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

bool	settings_are_set(t_game *game)
{
	if (game->no && game->so && game->ea && game->we && game->door
		&& game->floor_is_set && game->ceiling_is_set)
		return (true);
	return (false);
}

int	set_rgb(t_game *game, char *identifier, char **rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r > 255 || g > 255 || b > 255)
		return (ft_putstr_fd("Error!\nInvalid color value.\n", 2), 1);
	if (!ft_strcmp(identifier, "F"))
	{
		game->floor_color = (r << 16) | (g << 8) | b;
		game->floor_is_set = true;
	}
	else if (!ft_strcmp(identifier, "C"))
	{
		game->ceiling_color = (r << 16) | (g << 8) | b;
		game->ceiling_is_set = true;
	}
	return (0);
}

int	validate_and_set_rgb(t_game *game, char *identifier, char **rgb)
{
	int	i;
	int	j;

	if (!(rgb[0] && rgb[1] && rgb[2]) || rgb[3])
		return (ft_putstr_fd("Error!\nInvalid color format.\n", 2), 1);
	if (ft_strlen(rgb[0]) > 3 || ft_strlen(rgb[1]) > 3 || ft_strlen(rgb[2]) > 3)
		return (1);
	i = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (ft_putstr_fd("Error!\nInvalid color value.\n", 2), 1);
			j++;
		}
		i++;
	}
	return (set_rgb(game, identifier, rgb));
}

int	count_commas(char *colors)
{
	int	count;

	count = 0;
	while (*colors)
	{
		if (*colors == ',')
			count++;
		colors++;
	}
	return (count);
}

bool	is_texture_valid(t_game *game, char *path)
{
	void	*texture;
	int		height;
	int		width;

	texture = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!texture)
		return (false);
	mlx_destroy_image(game->mlx, texture);
	return (true);
}
