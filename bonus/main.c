#include "cub3D_bonus.h"

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
	printf("floor color = %X\n", game.floor_color);
	printf("ceiling color = %X\n", game.ceiling_color);
	printf("===================================\n");
	printf("north texture = *%s*\n", game.no);
	printf("south texture = *%s*\n", game.so);
	printf("east texture = *%s*\n", game.ea);
	printf("west texture = *%s*\n", game.we);
	for(int i = 0; game.map[i]; i++)
	printf("%s\n", game.map[i]);
}
