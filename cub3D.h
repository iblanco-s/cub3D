/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junesalaberria <junesalaberria@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:55:16 by jsalaber          #+#    #+#             */
/*   Updated: 2024/06/14 16:25:23 by junesalaber      ###   ########.fr       */
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
	char 	**split_map;
}	t_data;

//PARSE-check_1.c
int		check_split_letter(char *line);
int		check_split_texture(t_data *data, int count);
int		count_comma(char *p);
int		check_comma_position(char *line);
int		check_FC_fromat(char **split_texture);

//PARSE-check_2.c
int		check_duplicate(t_data *data);
int		check_surrounded_by_wall(char *line);
char	get_last_line(char **map);
int		check_lines(char **map);
int		surrounded_by_wall(char **map);

//PARSE-check_3.c
int		check_surrounded(char *line);
int		valid_map(char *line, int *count);

//PARSE-check.c
int		check_extension(char *file);
int		check_textures(char *line);
int		check_count_texture(t_data *data, int count);
int		check_map_content(t_data *data, int count);

//PARSE-parse.c
int		ft_error(char *str);
int		valid_map(char *line, int *count);

//PARSE-read_map.c
void	ft_free_readmap(char *line, char *texture, int fd);
void	ft_free_arr(char **arr);
char	*get_map(t_data *data);
void	ft_free_readmap(char *line, char *texture, int fd);

#endif