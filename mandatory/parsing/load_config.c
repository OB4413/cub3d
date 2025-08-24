/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:41:15 by ynadime           #+#    #+#             */
/*   Updated: 2025/08/24 15:41:16 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	set_texture(t_game *game, char *identifier, char *path)
{
	if ((!ft_strcmp(identifier, "NO") && game->no) || (!ft_strcmp(identifier,
				"SO") && game->so) || (!ft_strcmp(identifier, "EA") && game->ea)
		|| (!ft_strcmp(identifier, "WE") && game->we))
		return (ft_putstr_fd("Error!\nDuplicated texture identifiers.\n", 2),
			1);
	if (!ft_strcmp(identifier, "NO"))
		game->no = path;
	else if (!ft_strcmp(identifier, "SO"))
		game->so = path;
	else if (!ft_strcmp(identifier, "EA"))
		game->ea = path;
	else if (!ft_strcmp(identifier, "WE"))
	{
		game->we = path;
	}
	if (!is_texture_valid(game, path))
		return (1);
	return (0);
}

int	set_colors(t_game *game, char *identifier, char *color)
{
	char	**tokens;

	if ((!ft_strcmp(identifier, "F") && game->floor_is_set)
		|| (!ft_strcmp(identifier, "C") && game->ceiling_is_set))
		return (ft_putstr_fd("Error!\nDuplicated color identifiers.\n", 2), 1);
	if (count_commas(color) != 2)
		return (1);
	tokens = ft_split(color, ',');
	return (validate_and_set_rgb(game, identifier, tokens));
}

int	set_settings(t_game *game, char *line)
{
	char	**tokens;
	int		flag;

	tokens = ft_split_ws(line);
	if (!tokens[1] || tokens[2])
		return (ft_putstr_fd("Error!\nInvalid line format.\n", 2), 1);
	flag = 1;
	if (!ft_strcmp(tokens[0], "NO") || !ft_strcmp(tokens[0], "SO")
		|| !ft_strcmp(tokens[0], "EA") || !ft_strcmp(tokens[0], "WE"))
		flag = set_texture(game, tokens[0], tokens[1]);
	else if (!ft_strcmp(tokens[0], "F") || !ft_strcmp(tokens[0], "C"))
		flag = set_colors(game, tokens[0], tokens[1]);
	else
		ft_putstr_fd("Error!\nInvalid identifier.\n", 2);
	return (flag);
}

int	load_config(t_game *game, int fd)
{
	char	*line;

	line = ft_strtrim(get_next_line(fd), "\n");
	while (line)
	{
		if (!is_empty_line(line) && set_settings(game, line))
			return (1);
		if (settings_are_set(game))
			break ;
		line = ft_strtrim(get_next_line(fd), "\n");
	}
	if (!settings_are_set(game))
		return (ft_putstr_fd("Error!\nMissing settings.\n", 2), 1);
	return (0);
}
