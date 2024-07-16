/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:55:16 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/16 11:32:46 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# include <stdint.h>
# include <stdarg.h>

# define WW 1920
# define WH 1080
# define FOV 60
# define TILE_SIZE 64
# define PI 3.14159265358979323846
# define ROTATION_SPEED 0.042
# define MOVE_SPEED 3

typedef struct s_param
{
	mlx_texture_t	*texture;
	double			ip_x;
	double			ip_y;
	double			scale;
}	t_param;

typedef struct s_text
{
	char			*value;
	char			*path;
	struct s_text	*next;
}	t_text;

typedef struct s_tex
{
	mlx_texture_t	*ea;
	mlx_texture_t	*we;
	mlx_texture_t	*so;
	mlx_texture_t	*no;
}	t_tex;

typedef struct s_data
{
	int		fd;
	char	*line;
	char	*texture;
	char	**split_texture;
	char	*map;
	char	**split_map;
	char	**map_copy;
	int		map_height;
	int		map_width;
	int		player_x;
	int		player_y;
	int		map_column;
	int		map_lines;
	char	**floor;
	char	**ceiling;
	t_text	*texture_list;
}	t_data;

typedef struct s_player
{
	int		playr_x;
	int		playr_y;
	double	playr_dir;
	float	fov_rad;
	int		rotate;
	int		h_move;
	int		v_move;
	int		mouse_x;
	int		mouse_y;
}	t_player;

typedef struct s_ray
{
	double		ray_angle;
	double		wall_h_x;
	double		wall_h_y;
	double		wall_v_x;
	double		wall_v_y;
	double		distance;
	int			index;
	int			flag;
}	t_ray;

typedef struct s_mlx
{
	mlx_t			*mlx_ptr;
	mlx_image_t		*img;
	t_data			*dat;
	t_player		*play;
	t_ray			*ray;
	t_text			*mlx_texture;
	t_tex			*tex;
	mouse_mode_t	mouse;
}	t_mlx;

//PARSE-check_1.c
int				check_split_letter(char *line);
int				check_split_texture(char **split_texture, int count);
int				count_comma(char *p);
int				check_comma_position(char *line);
int				check_fc_fromat(char **split_texture);

//PARSE-check_2.c
int				check_duplicate(t_data *data);
int				check_line_round_by_wall(char *line);
char			*get_last_line(char **map);
int				check_lines(char **map);
int				surrounded_by_wall(char **map);

//PARSE-check_3.c
int				check_column_round_by_wall(char *line);
int				valid_map(char *line, int *count);

//PARSE-check.c
int				check_extension(char *file);
int				check_textures(char *line);
int				count_texture(t_data *data, int count);
char			*get_map(t_data *data);
int				check_map_content(t_data *data, int count);

//PARSE-read_map.c
void			ft_free_readmap(char *line, char *texture, int fd);
void			ft_free_arr(char **arr);
int				read_map(char *argv, t_data *data, int *count);
void			ft_freemap(t_data *data);

//PARSE-map_size1.c
int				map_len(char **map);
int				line_maxlen(char **map);
char			*adjust_line(char *line, int max_len);
int				manage_spaces_width(char **map);
int				manage_spaces_height(char **map);

//PARSE-map_size.c
int				map_size(t_data *data);

//PARSE-texture_1.c
int				ft_list_texture(t_data *data, t_text **mlx_texture);

//PARSE-texture_2.c
int				check_color(t_data *data, t_text *mlx_texture);

//PARSE-parse.c
int				ft_error(char *str);
void			get_player_position(t_data *data);
void			get_lines_column(t_data *data);
int				parse(int argc, char **argv, t_data *data, t_text *tx);

//RAYCASTING-exec.c
int				exec(t_data *dat);

//RAYCASTING-load_texture.c
int				load_all_textures(t_tex *tex, t_text *texture);

//RAYCASTING-move.c
void			execute_player_move(t_mlx *mlx, double move_x, double move_y);
void			key_pressed(mlx_key_data_t keycode, void *param);

//RAYCASTING-exit.c
void			free_textures(t_text *texture_list);
void			ft_exit(t_mlx *mlx);

//RAYCASTING.c-raycasting_2.c
void			ft_put_pixel(t_mlx *mlx, int x, int y, int color);
void			draw_wall_segment(t_mlx *mlx, int ray);
int				get_rgba(int r, int g, int b, int a);

//RAYCASTING.c-raycasting_3.c
int				reverse_bytes(int num);
float			normalize_angle(float angle);
mlx_texture_t	*get_texture(t_mlx *mlx, int flag);
double			get_impact_point(mlx_texture_t *texture, t_mlx *mlx);
int				unit_circle(float angle, char axis);

//RAYCASTING.c-raycasting_4.c
void			raycasting(t_mlx *mlx);

//RAYCASTING.c-raycasting_5.c
void			wall_params(t_mlx *mlx, int u_pix, double wall_height,
					t_param *params);
void			draw_wall_pixels(t_mlx *mlx, int d_pix, int u_pix,
					t_param *params);

//MINIMAP.c
void			draw_minimap(t_mlx *mlx);
void			draw_player(t_mlx *mlx);
void			draw_ray_minimap(t_mlx *mlx, double x, double y);

#endif