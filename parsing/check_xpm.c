/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/05 11:15:57 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\n')
		return (1);
	else
		return (0);
}

int	search_xpm(char *file_path)
{
	int		len;
	char	*str;

	if (!file_path)
		return (0);
	str = ft_strtrim(file_path, "\n\r\t");
	len = ft_strlen(str);
	if (len < 4)
		return (0);
	return (str[len - 4] == '.' && str[len - 3] == 'x' && str[len - 2] == 'p'
		&& str[len - 1] == 'm');
}

void	check_xpm(t_game *game)
{
	if (!search_xpm(game->north_texture) || !search_xpm(game->east_texture)
		|| !search_xpm(game->west_texture) || !search_xpm(game->south_texture))
	{
		ft_putstr_fd("Error: \nInvalid .xpm texture file extension\n", 2);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
}
