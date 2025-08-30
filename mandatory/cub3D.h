/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:36:49 by obarais           #+#    #+#             */
/*   Updated: 2025/08/30 12:16:12 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <X11/keysym.h>
# include <X11/X.h>
# include <mlx.h>
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define FT_ALLOC 1
# define FT_CLEAR 0
# define MAX_LINES 100
# define TILE 64
# define MINTILE 8
# define WIN_WIDTH 1000
# define WIN_HEIGHT 600
# define MINMAP_WI 166.666666667
# define MINMAP_HE 100
# define FOV 1.0471975512
# define SPED 1.5
# define SPED_RL 0.008
# define STEP 0.00104719755

typedef struct s_ray
{
	double	hit_x;
	double	hit_y;
}			t_ray;

typedef struct s_alloc_list
{
	void				*ptr;
	struct s_alloc_list	*next;
}						t_alloc_list;

typedef struct s_game
{
	void	**pst_imag;
	void	*d_p_imag;
	int		pbpp;
	int		psl;
	int		pend;
	int		i;
	int		keys[65365];
	char	char_color;
	int		map_height;
	int		bits_per_pixel;
	int		bpp;
	int		size_line;
	int		sl;
	int		endian;
	int		en;
	void	*d_imag;
	void	*d_imag_v;
	void	*d_nsew;
	void	*imag;
	void	*imag_v;
	double	dist;
	void	*win;

	double	distances_x;
	double	distances_y;
	double	ray_angle;
	double	angle;
	t_ray	*x;
	t_ray	*y;
	double	hx;
	double	hy;
	double	ya;
	double	yb;
	double	xa;
	double	xb;
	int		x_or_y;
	int		ng;
	int		shot;
	int		h;
	void	*n_image;
	int		yn;
	int		xn;
	void	*s_image;
	int		ys;
	int		xs;
	void	*e_image;
	int		ye;
	int		xe;
	void	*w_image;
	int		yw;
	int		xw;
	void	*door_imag;
	int		yd;
	int		xd;
	int		imag_height;
	int		imag_width;
	int		wall_height;
	double	ofs_tex;
	int		jump;
	int		index_jumb;

	float	player_x;
	float	player_y;
	char	player_char;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	void	*mlx;
	char	**map;
	int		floor_color;
	int		ceiling_color;
	bool	floor_is_set;
	bool	ceiling_is_set;
}			t_game;

int			close_window(t_game *game);
void		cleanup_game(t_game *game);
void		ft_free(void *ptr);
void		free_memory(void);
void		*ft_malloc(size_t size);
void		destroy_images(t_game *game);
void		ft_destroy_image(void *mlx, void *img);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char const *s, char c);
char		**ft_split_ws(char const *s);
int			ft_isspace(char c);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
void		ft_putstr_fd(char *s, int fd);
bool		is_empty_line(char *line);
int			parse_file(char *path, t_game *game);
int			load_config(t_game *game, int fd);
int			load_map(t_game *game, int fd);
int			check_map(t_game *game);
int			validate_and_set_rgb(t_game *game, char *identifier, char **rgb);
bool		settings_are_set(t_game *game);
int			count_commas(char *colors);
bool		is_valid_filename(char *filename);
void		raycaster(t_game *game);
void		drow_imag_in(t_game *g, int x, int *y, int start);
bool		is_texture_valid(t_game *game, char *path);
int			is_wall(double x, double y, t_game *game, double angle_offset);
void		normalize_angle(t_game *game);
int			ftk_strlen(char *str);
void		the_distance_with_y(t_game *g, int i, double step_x, double step_y);
void		the_distance_with_x(t_game *g, int i, double step_x, double step_y);
double		dda(t_game *game, int facing_down, int facing_right);
void		draw_view(t_game *game, int x, double dist, char *dst);
void		drow_imag_player(t_game *g, int x, int y, char *st);
void		init_imag_player(t_game *g, int x);
int			prees_key(int key, t_game *game);
int			release_key(int key, t_game *game);
void		chose_the_angle_p(t_game *game);
void		change_line_to_null(t_game *game);
void		move_player11(t_game *game, double angle_offset);
int			update_position_player(t_game *game);
int			raycasting(t_game *game);

#endif
