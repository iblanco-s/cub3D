/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:52:44 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/16 17:37:57 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	ft_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (0);
}

void	get_player_position(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map_copy[i])
	{
		j = 0;
		while (data->map_copy[i][j])
		{
			if (data->map_copy[i][j] == 'N' || data->map_copy[i][j] == 'S'
				|| data->map_copy[i][j] == 'W' || data->map_copy[i][j] == 'E')
			{
				data->player_x = j;
				data->player_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	get_lines_column(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->map_column = 0;
	while (data->split_map[i])
	{
		j = 0;
		while (data->split_map[i][j])
			j++;
		if (j > data->map_column)
			data->map_column = j;
		i++;
	}
	data->map_lines = i;
}

void	ft_data_init(t_data *data)
{
	if (!data)
		return ;
	data->fd = -1;
	data->line = NULL;
	data->texture = NULL;
	data->split_texture = NULL;
	data->map = NULL;
	data->split_map = NULL;
	data->map_copy = NULL;
	data->map_height = 0;
	data->map_width = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->map_column = 0;
	data->map_lines = 0;
	data->floor = NULL;
	data->ceiling = NULL;
	data->texture_list = NULL;
}

int	parse(int argc, char **argv, t_data *data, t_text *list_texture)
{
	int	count;

	list_texture = NULL;
	if (argc != 2 || !check_extension(argv[1]))
	{
		ft_error("Error\nWrong argument\n");
		exit(1);
	}
	count = 0;
	if (!read_map(argv[1], data, &count))
		return (0);
	if (!map_size(data))
		return (0);
	if (!ft_list_texture(data, &list_texture))
		return (free_textures(list_texture), ft_freemap(data), 0);
	if (!check_color(data, list_texture))
		return (free_textures(list_texture), ft_freemap(data), 0);
	get_player_position(data);
	get_lines_column(data);
	data->texture_list = list_texture;
	return (1);
}
