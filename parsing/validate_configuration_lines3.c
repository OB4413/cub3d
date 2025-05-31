/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_configuration_lines3.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/05 11:11:15 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	process_door(t_game *game, int *config_count, char *line, int *flags)
{
	if (!ft_strncmp(line, "DOOR_CLOSED ", 12))
	{
		if (flags[6])
			handle_init_errors(3);
		flags[6] = 1;
		handle_texture_line(line, &game->door_closed, config_count);
	}
	else if (!ft_strncmp(line, "DOOR_OPEN ", 10))
	{
		if (flags[7])
			handle_init_errors(3);
		flags[7] = 1;
		handle_texture_line(line, &game->door_closed, config_count);
	}
}

void	process_anim(t_game *game, int *config_count, char *line, int *flags)
{
	if (!ft_strncmp(line, "ANIM_0 ", 7))
	{
		if (flags[8])
			handle_init_errors(3);
		flags[8] = 1;
		handle_texture_line(line, &game->anim_0, config_count);
	}
	else if (!ft_strncmp(line, "ANIM_1 ", 7))
	{
		if (flags[9])
			handle_init_errors(3);
		flags[9] = 1;
		handle_texture_line(line, &game->anim_1, config_count);
	}
}

void	process_key(t_game *game, int *config_count, char *line, int *flags)
{
	if (!ft_strncmp(line, "KEY ", 4))
	{
		if (flags[10])
			handle_init_errors(3);
		flags[10] = 1;
		handle_texture_line(line, &game->key, config_count);
	}
}
