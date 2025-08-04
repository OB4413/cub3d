#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
#include <stdio.h>
# include <mlx.h>

typedef struct s_game
{
    char *no;
    char *so;
    char *ea;
    char *we;
    char *door;
    void *mlx;
    char **map;
    int floor_color;
    int ceiling_color;
    bool floor_is_set;
    bool ceiling_is_set;
}		t_game;

int	    ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	**ft_split_ws(char const *s);
int	    ft_isspace(char c);
int	    ft_isdigit(int c);
int     ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putstr_fd(char *s, int fd);
bool    is_empty_line(char *line);
int     parse_file(char *path, t_game *game);
int	load_config(t_game *game, int fd);
int	load_map(t_game *game, int fd);
int check_map(t_game *game);
int	validate_and_set_rgb(t_game *game, char *identifier, char **rgb);
bool	settings_are_set(t_game *game);
int	count_commas(char *colors);
bool	is_valid_filename(char *filename);

#endif