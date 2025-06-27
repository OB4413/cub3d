/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/06/20 09:18:34 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif
# define FT_ALLOC 1
# define FT_CLEAR 0
# define MAX_LINES 100
# define TILE 60
# define MINTILE 8
# define WIN_WIDTH 1000
# define WIN_HEIGHT 600
#define MINMAP_WI (WIN_WIDTH / 6)
#define MINMAP_HE (WIN_HEIGHT / 6)
# define FOV (M_PI / 3)
# define SPED 1
# define SPED_RL 0.009

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_ray {
	double	hit_x;
	double	hit_y;
}	t_ray;

typedef struct s_game
{
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
	void			*imag;
	void			*imag_v;
	double			dist;
	void			*mlx;
	void			*win;
	char			**map;
	char			**map_section;
	char			**map_copy;
	int				fd;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*door_closed;
	char			*door_open;
	char			*key;
	char			*anim_0;
	char			*anim_1;
	int				floor_color[3];
	int				ceiling_color[3];
	int				map_start_index;
	int				max_len;
	float			player_x;
	float			player_y;
	char			player_char;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
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
}					t_game;


void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
t_list				*ft_lstnew(void *content);
char				**ft_split2(char *str, char *charset);
char				*ft_strcpy(char *dest, char const *src);
char				*ft_strcat(char *dest, char const *src);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strdup(const char *src);
size_t				ft_strlen(const char *c);
void				*ft_memset(void *s, int c, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strndup(const char *s, size_t n);
t_list				*mem_alloc(size_t size);
void				*ft_malloc(size_t size, short option);
int					parse_map(const char *file_path, t_game *game);
void				handle_init_errors(int error_type);
void				ft_putstr_fd(char *str, int fd);
void				read_map_lines(t_game *game);
char				*extract_path(char *str);
void				validate_configuration_lines(t_game *game);
int					is_empty_line(char *str);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
int					is_all_digits(const char *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
char				*ft_strtrim(char const *s1, char const *set);
void				extract_number(char *str, t_game *game, int number);
void				check_xpm(t_game *game);
void				map_section(t_game *game);
int					ft_strcmp(const char *s1, const char *s2);
int					is_config_identifier(char *line);
void				handle_texture_line(char *line, char **texture, int *count);
void				handle_color_line(char *line, t_game *game, int type,
						int *count);
void				process_no_so(t_game *game, int *config_count, char *line,
						int *flags);
int					process_config_lines(t_game *game, int *config_flags);
void				validate_configuration_lines(t_game *game);
void				set_up_map(t_game *game);
void				flood_fill(char **map, int y, int x);
void				set_player_direction(t_game *game);
void				process_door(t_game *game, int *config_count, char *line,
						int *flags);
void				process_anim(t_game *game, int *config_count, char *line,
						int *flags);
void				process_key(t_game *game, int *config_count, char *line,
						int *flags);
void				raycaster(t_game **game);

#endif
