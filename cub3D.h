/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:55:16 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/01 11:43:36 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdbool.h>

# define WW 800
# define WH 600
# define FOV 60
# define TILE_SIZE 64

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
}	t_player;

typedef struct s_ray
{
	double		ray_angle;
	double		wall_hith_x;
	double		wall_hith_y;
	double		wall_hitv_x;
	double		wall_hitv_y;
	double		distance;
}	t_ray;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_data		*dat;
	t_player	*play;
	t_ray		*ray;
	t_text		*mlx_texture;
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
bool	load_texture(t_texture *texture, void *mlx_ptr, t_text *list_texture);
bool	load_all_textures(t_data *data, t_mlx *mlx);

//RAYCASTING-exit.c
void	free_textures(t_text *texture_list);
void	ft_exit(t_mlx *mlx);

//RAYCASTING.c
int		raycasting(t_mlx *mlx, t_data data);

#endif