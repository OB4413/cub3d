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
