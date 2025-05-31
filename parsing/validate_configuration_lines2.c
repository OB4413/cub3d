/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_configuration_lines2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/05 11:18:47 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	process_we_ea(t_game *game, int *config_count, char *line,
		int *flags)
{
	if (!ft_strncmp(line, "WE ", 3))
	{
		if (flags[2])
			handle_init_errors(3);
		flags[2] = 1;
		handle_texture_line(line, &game->west_texture, config_count);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		if (flags[3])
			handle_init_errors(3);
		flags[3] = 1;
		handle_texture_line(line, &game->east_texture, config_count);
	}
}

static void	process_f_c(t_game *game, int *config_count, char *line, int *flags)
{
	if (!ft_strncmp(line, "F ", 2))
	{
		if (flags[4])
			handle_init_errors(3);
		flags[4] = 1;
		handle_color_line(line, game, 1, config_count);
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		if (flags[5])
			handle_init_errors(3);
		flags[5] = 1;
		handle_color_line(line, game, 2, config_count);
	}
}

static void	process_config_line2(t_game *game, int *config_count, char *line,
		int *flags)
{
	while (*line == ' ' || *line == '\t' || *line == '\r')
		line++;
	process_no_so(game, config_count, line, flags);
	process_we_ea(game, config_count, line, flags);
	process_f_c(game, config_count, line, flags);
	process_key(game, config_count, line, flags);
	process_anim(game, config_count, line, flags);
	process_door(game, config_count, line, flags);
	if (!is_config_identifier(line) && *line && !is_empty_line(line))
	{
		ft_putstr_fd("Error: \nInvalid config line\n", 2);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
}

int	is_config_identifier(char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2)
		|| !ft_strncmp(line, "DOOR_CLOSED ", 12) || !ft_strncmp(line,
			"DOOR_OPEN ", 10) || !ft_strncmp(line, "KEY ", 4)
		|| !ft_strncmp(line, "ANIM_0 ", 7) || !ft_strncmp(line, "ANIM_1 ", 7))
		return (1);
	return (0);
}

int	process_config_lines(t_game *game, int *config_flags)
{
	int		config_count;
	int		i;
	char	*line;

	config_count = 0;
	i = 0;
	while (game->map[i])
	{
		if (is_empty_line(game->map[i]))
		{
			i++;
			continue ;
		}
		line = game->map[i];
		while (*line == ' ' || *line == '\t' || *line == '\r')
			line++;
		if (is_config_identifier(line))
			process_config_line2(game, &config_count, game->map[i],
				config_flags);
		else
			break ;
		i++;
	}
	return (i);
}
