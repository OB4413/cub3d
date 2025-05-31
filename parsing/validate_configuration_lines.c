/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_configuration_lines.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/05 11:15:01 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_texture_line(char *line, char **texture, int *count)
{
	*texture = extract_path(line);
	(*count)++;
}

void	handle_color_line(char *line, t_game *game, int type, int *count)
{
	extract_number(line, game, type);
	(*count)++;
}

void	process_no_so(t_game *game, int *config_count, char *line, int *flags)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (flags[0])
			handle_init_errors(3);
		flags[0] = 1;
		handle_texture_line(line, &game->north_texture, config_count);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (flags[1])
			handle_init_errors(3);
		flags[1] = 1;
		handle_texture_line(line, &game->south_texture, config_count);
	}
}

void	check_duplicate_textures(t_game *game)
{
	if (ft_strcmp(game->north_texture, game->south_texture) == 0
		|| ft_strcmp(game->north_texture, game->west_texture) == 0
		|| ft_strcmp(game->north_texture, game->east_texture) == 0
		|| ft_strcmp(game->south_texture, game->west_texture) == 0
		|| ft_strcmp(game->south_texture, game->east_texture) == 0
		|| ft_strcmp(game->west_texture, game->east_texture) == 0)
	{
		ft_putstr_fd("Error: \nDuplicate texture files are not allowed\n", 2);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
}

void	validate_configuration_lines(t_game *game)
{
	int	config_flags[11];
	int	i;
	int	j;

	j = 0;
	while (j < 11)
		config_flags[j++] = 0;
	i = process_config_lines(game, config_flags);
	game->map_start_index = i;
	j = 0;
	while (j < 11)
		if (config_flags[j++] != 1)
			handle_init_errors(2);
	check_duplicate_textures(game);
	check_xpm(game);
}
