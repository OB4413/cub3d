/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/05 11:14:06 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	search_cub(const char *file_path)
{
	size_t	len;

	if (!file_path)
		return (0);
	len = ft_strlen(file_path);
	if (len < 4)
		return (0);
	return (file_path[len - 4] == '.' && file_path[len - 3] == 'c'
		&& file_path[len - 2] == 'u' && file_path[len - 1] == 'b');
}

char	*extract_path(char *str)
{
	int		i;
	int		j;
	char	*res;
	char	*res2;

	res = ft_malloc(ft_strlen(str), FT_ALLOC);
	i = 2;
	j = 0;
	while (str[i] != '\0')
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	res2 = ft_strtrim(res, " \n");
	return (res2);
}

void	read_map_lines(t_game *game)
{
	int	i;

	i = 0;
	game->map = ft_malloc(sizeof(char *) * MAX_LINES, FT_ALLOC);
	game->map[0] = get_next_line(game->fd);
	if (!game->map[0])
	{
		ft_putstr_fd("error: \nMap is empty\n", 2);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	while (game->map[i] != NULL)
	{
		i++;
		game->map[i] = get_next_line(game->fd);
	}
	validate_configuration_lines(game);
}

int	parse_map(const char *file_path, t_game *game)
{
	if (!search_cub(file_path))
	{
		if (file_path)
			write(STDERR_FILENO, "Error: \nFile should be .cub\n", 28);
		return (-1);
	}
	game->fd = open(file_path, O_RDONLY);
	if (game->fd == -1)
	{
		perror("open failed");
		return (-1);
	}
	read_map_lines(game);
	map_section(game);
	return (0);
}
