/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:37:07 by obarais           #+#    #+#             */
/*   Updated: 2025/08/23 13:31:35 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../minilibx-linux/mlx.h"
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
# define WIN_WIDTH 1020
# define WIN_HEIGHT 600
# define MINMAP_WI 170
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

typedef struct s_game
{
	void	**ak_imag;
	void	**mg_imag;
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
	char	*door;
	void	*mlx;
	char	**map;
	int		floor_color;
	int		ceiling_color;
	bool	floor_is_set;
	bool	ceiling_is_set;
}			t_game;

int			ft_strcmp(char *s1, char *s2);
char		*ft_itoa(int n);
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
void		draw_view(t_game *game, int x, double dist, int y);
double		dda(t_game *game, int facing_down, int facing_right);
void		chose_the_angle_p(t_game *game);
int			prees_key(int key, t_game *game);
int			release_key(int key, t_game *game);
int			mouse_move(int x, int y, t_game *g);
int			update_position_player(t_game *game, int x, int y);
void		move_player11(t_game *game, double angle_offset);
int			ftk_strlen(char *str);
int			check_the_dor(t_game *g, double y, double x, int v);
int			is_wall(double x, double y, t_game *game);
void		normalize_angle(t_game *game);
void		open_and_close_door(t_game *g);
void		change_the_gane(t_game *g);
void		draw_minimap(t_game *g);
void		drow_imag_player(t_game *g, int x, int y);
int			loop_chose_gun(t_game *g, int x, int y);
int			raycasting(t_game *game);
void		change_line_to_null(t_game *game);
void		init_imag_player(t_game *g, int x, int y);
int			shot_gun(int butom, int x, int y, t_game *game);
int			stop_gun(int butom, int x, int y, t_game *game);
void		raycaster(t_game *game);
void		help_raycaster(t_game *game);
double		help_dda(t_game *g, int facing_right);

#endif
