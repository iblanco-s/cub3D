/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:55:16 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/04 14:01:06 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# include <stdint.h>
# include "minilibx-linux/mlx_int.h"

# define WW 800
# define WH 600
# define FOV 60
# define TILE_SIZE 64
# define PI 3.14159265358979323846
# define ROTATION_SPEED 0.042
# define MOVE_SPEED 0.05
# define ESC 65307
# define W   119
# define A   97
# define S   115
# define D   100
# define LEFT 65361
# define RIGHT 65363

typedef struct s_texture
{
	void	*img;
	bool	created;
}	t_texture;

typedef struct s_text
{
	char			*value;
	char			*path;
	struct s_text	*next;
	t_texture		*texture;
}	t_text;

typedef struct s_tex
{
	t_img	*ea;
	t_img	*we;
	t_img	*so;
	t_img	*no;
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
	void		*mlx;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_data;
	int			size_line;
	int			bpp;
	int			endian;
	t_data		*dat;
	t_player	*play;
	t_ray		*ray;
	t_texture	*texture;
	t_text		*mlx_texture;
	t_tex		*tex;
}	t_mlx;

//PARSE-check_1.c
int		check_split_letter(char *line);
int		check_split_texture(char **split_texture, int count);
int		count_comma(char *p);
int		check_comma_position(char *line);
int		check_fc_fromat(char **split_texture);

//PARSE-check_2.c
int		check_duplicate(t_data *data);
int		check_line_round_by_wall(char *line);
char	*get_last_line(char **map);
int		check_lines(char **map);
int		surrounded_by_wall(char **map);

//PARSE-check_3.c
int		check_column_round_by_wall(char *line);
int		valid_map(char *line, int *count);

//PARSE-check.c
int		check_extension(char *file);
int		check_textures(char *line);
int		count_texture(t_data *data, int count);
char	*get_map(t_data *data);
int		check_map_content(t_data *data, int count);

//PARSE-read_map.c
void	ft_free_readmap(char *line, char *texture, int fd);
void	ft_free_arr(char **arr);
int		read_map(char *argv, t_data *data, int *count);
void	ft_freemap(t_data *data);

//PARSE-map_size1.c
int		map_len(char **map);
int		line_maxlen(char **map);
char	*adjust_line(char *line, int max_len);
int		manage_spaces_width(char **map);
int		manage_spaces_height(char **map);

//PARSE-map_size.c
int		map_size(t_data *data);

//PARSE-texture_1.c
int		ft_list_texture(t_data *data, t_text **mlx_texture);

//PARSE-texture_2.c
int		check_color(t_data *data, t_text *mlx_texture);

//PARSE-parse.c
int		ft_error(char *str);
void	get_player_position(t_data *data);
void	get_lines_column(t_data *data);
int		parse(int argc, char **argv, t_data *data, t_text *tx);

//RAYCASTING-exec.c
void	create_window(t_mlx *mlx);
int		exec(t_data *dat);

//RAYCASTING-load_texture.c
bool	load_texture(t_mlx *mlx, t_text *tx);
bool	load_all_textures(t_data *data, t_mlx *mlx);

//RAYCASTING-move.c
void	execute_player_move(t_mlx *mlx, double move_x, double move_y);
int		key_pressed(int keycode, void *param);

//RAYCASTING-exit.c
void	free_textures(t_text *texture_list);
void	ft_exit(t_mlx *mlx);

//RAYCASTING.c-raycasting_2.c
void	draw_wall_segment(t_mlx *mlx, int ray);
void	draw_floor_ceiling(t_mlx *mlx, int ray, int d_pix, int u_pix);

//RAYCASTING.c-raycasting_3.c
int		reverse_bytes(int num);
float	normalize_angle(float angle);
void	*get_texture(t_mlx *mlx, int flag);
double	get_impact_point(t_img *img, t_mlx *mlx);
int		unit_circle(float angle, char axis);

//RAYCASTING.c-raycasting_4.c
void	raycasting(t_mlx *mlx);

#endif