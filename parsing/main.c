/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/29 09:50:58 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_init_errors(int error_type)
{
	ft_malloc(0, FT_CLEAR);
	if (error_type == 1)
		ft_putstr_fd("Error: \nInvalid arguments\n", 2);
	else if (error_type == 2)
		ft_putstr_fd("Error: \nFailed to parse map\n", 2);
	else if (error_type == 3)
		ft_putstr_fd("Error: \nDuplicate configuration element\n", 2);
	else if (error_type == 4)
		ft_putstr_fd("Error: \nUndefined char\n", 2);
	else if (error_type == 5)
		ft_putstr_fd("Error: \nNo player found\n", 2);
	else if (error_type == 6)
		ft_putstr_fd("Error: \nMap not closed\n", 2);
	exit(1);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = ft_malloc(sizeof(t_game), FT_ALLOC);
	if (ac != 2)
		handle_init_errors(1);
	else if (parse_map(av[1], game) == -1)
		handle_init_errors(2);
	raycaster(&game);
	ft_malloc(0, FT_CLEAR);
	return (0);
}
