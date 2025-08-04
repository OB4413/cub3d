#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "get_next_line/get_next_line.h"
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif
# define FT_ALLOC 1
# define FT_CLEAR 0
# define MAX_LINES 100
# define TILE 64
# define MINTILE 8
# define WIN_WIDTH 1000
# define WIN_HEIGHT 600
#define MINMAP_WI (WIN_WIDTH / 6)
#define MINMAP_HE (WIN_HEIGHT / 6)
# define FOV (M_PI / 3)
# define SPED 1.5
# define SPED_RL 0.008
# define STEP (FOV / WIN_WIDTH)

typedef struct s_ray {
	double	hit_x;
	double	hit_y;
}	t_ray;

typedef struct s_game
{
    void			**ak_imag;
	void			**mg_imag;
	void			**pst_imag;
	void			*d_p_imag;
	int				pbpp;
	int				psl;
	int				pend;
	int 			i;
	int				keys[65365];
	char 			char_color;
	int				map_height;
	int				bits_per_pixel;
	int				bpp;
	int				size_line;
	int				sl;
	int				endian;
	int				en;
	void			*d_imag;
	void			*d_imag_v;
	void			*d_nsew;
	void			*imag;
	void			*imag_v;
	double			dist;
	void			*win;


    double			distances_x;
	double			distances_y;
	double			ray_angle;
	double			angle;
	t_ray			*x;
	t_ray			*y;
	double			hx;
	double			hy;
	double			ya;
	double			yb;
	double			xa;
	double			xb;
	int				x_or_y;
	int				ng;
	int				shot;
	int				h;
	void			*n_image;
	int				yn;
	int				xn;
	void			*s_image;
	int				ys;
	int				xs;
	void			*e_image;
	int				ye;
	int				xe;
	void			*w_image;
	int				yw;
	int				xw;
	void			*door_imag;
	int				yd;
	int				xd;
	int				imag_height;
	int				imag_width;
	int				wall_height;
	double			ofs_tex;
	int				jump;
	int				index_jumb;

    float	player_x;
	float	player_y;
    char    player_char;
    char *no;
    char *so;
    char *ea;
    char *we;
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
void    	raycaster(t_game *game);
void	drow_imag_in(t_game *g, int x, int *y, int start);
bool	is_texture_valid(t_game *game, char *path);

#endif
