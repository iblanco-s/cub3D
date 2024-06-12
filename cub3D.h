/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:55:16 by jsalaber          #+#    #+#             */
/*   Updated: 2024/06/12 12:33:59 by jsalaber         ###   ########.fr       */
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
	char	*split_texture;
}	t_data;

//PARSE-check.c
int	check_extension(char *file);
int	check_textures(char *line);
int	check_count_texture(t_data *data, int count);

//PARSE-parse.c
int	ft_error(char *str);

#endif