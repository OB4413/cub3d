/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:24:13 by obarais           #+#    #+#             */
/*   Updated: 2025/08/25 15:28:54 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_valid_filename(char *filename)
{
	if (ft_strlen(filename) < 5 || ft_strncmp(&filename[ft_strlen(filename)]
			- 4, ".cub", 4) || !ft_strncmp(&filename[ft_strlen(filename)] - 5,
			"/.cub", 5))
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	game.mlx = mlx_init();
	if (ac != 2 || is_valid_filename(av[1]) == false)
		return (ft_putstr_fd("Error\nUsage: ./cub3D <mapfile.cub>\n", 2), 1);
	if (parse_file(av[1], &game))
		return (1);
	raycaster(&game);
}
