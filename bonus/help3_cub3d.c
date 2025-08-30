/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help3_cub3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:23:33 by obarais           #+#    #+#             */
/*   Updated: 2025/08/30 19:06:32 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	help_is_wall(double angle_offset, t_game *g, int x, int y)
{
	int	facing_right;
	int	facing_down;

	facing_down = (g->angle + angle_offset > 0 && g->angle
			+ angle_offset < M_PI);
	facing_right = (g->angle + angle_offset < M_PI / 2 || g->angle
			+ angle_offset > 3 * M_PI / 2);
	if (facing_down && facing_right)
	{
		if (g->map[y][x + 1] == '1' && g->map[y + 1][x] == '1')
			return (1);
	}
	else if (facing_down && !facing_right)
	{
		if (g->map[y][x - 1] == '1' && g->map[y + 1][x] == '1')
			return (1);
	}
	else if (!facing_down && facing_right && g->map[y][x + 1]
		== '1' && g->map[y - 1][x] == '1')
		return (1);
	else if (!facing_down && !facing_right && g->map[y][x - 1]
		== '1' && g->map[y - 1][x] == '1')
		return (1);
	return (0);
}
