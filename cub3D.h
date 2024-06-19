/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:55:16 by jsalaber          #+#    #+#             */
/*   Updated: 2024/06/19 10:32:37 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
//# include "minilibx-linux/mlx.h"
# include <unistd.h>

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
}	t_data;

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

//PARSE-map_size1.c
int		map_len(char **map);
int		line_maxlen(char **map);
char	*adjust_line(char *line, int max_len);
int		manage_spaces_width(char **map);
int		manage_spaces_height(char **map);

//PARSE-map_size.c
int		map_size(t_data *data);

//PARSE-parse.c
int		ft_error(char *str);
void	get_player_position(t_data *data);
void	get_lines_column(t_data *data);
int		parse(int argc, char **argv, t_data *data);

#endif