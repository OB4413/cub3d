/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/02 20:44:07 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	validate_color_components(char **components)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (components[i] != NULL)
	{
		trimmed = ft_strtrim(components[i], " \n\r\t");
		if (!is_all_digits(trimmed))
		{
			ft_putstr_fd("Error: \nNot a number\n", 2);
			ft_malloc(0, FT_CLEAR);
			exit(1);
		}
		i++;
	}
	if (i != 3)
		handle_init_errors(2);
}

static void	set_color_values(t_game *game, char **components, int type)
{
	int	*color_array;
	int	i;

	i = 0;
	while (components[i])
		i++;
	if (i != 3)
	{
		ft_putstr_fd("Error: \nRGB must have exactly 3 values\n", 2);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	if (type == 1)
		color_array = game->floor_color;
	else
		color_array = game->ceiling_color;
	color_array[0] = ft_atoi(components[0]);
	color_array[1] = ft_atoi(components[1]);
	color_array[2] = ft_atoi(components[2]);
}

static char	*prepare_color_string(char *str)
{
	char	*str2;
	int		i;

	i = 0;
	str += 1;
	while (*str == ' ' && *str)
		str++;
	str2 = ft_malloc(ft_strlen(str) + 1, FT_ALLOC);
	while (*str)
		str2[i++] = *str++;
	str2[i] = '\0';
	return (str2);
}

void	count_comma(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
	{
		ft_putstr_fd("error : \nin comma\n", 2);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
}

void	extract_number(char *str, t_game *game, int number)
{
	char	**components;
	char	*processed_str;

	count_comma(str);
	processed_str = prepare_color_string(str);
	components = ft_split2(processed_str, ",");
	validate_color_components(components);
	set_color_values(game, components, number);
}
