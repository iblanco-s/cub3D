/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junesalaberria <junesalaberria@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:00:09 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/12 16:04:59 by junesalaber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	check_extension(char *file)
{
	char	*dot;

	dot = ft_strrchr(file, '.');
	if (dot && !ft_strncmp(dot, ".cub", 4))
		return (1);
	else if (!file || !dot)
		return (0);
	return (0);
}

int	check_textures(char *line)
{
	while (*line == ' ' || (*line >= 9 && *line <= 13))
		line++;
	if ((!strncmp(line, "NO", 2) || !strncmp(line, "SO", 2)
			|| !strncmp(line, "WE", 2) || !strncmp(line, "EA", 2))
		|| !strncmp(line, "F", 1) || !strncmp(line, "C", 1))
		return (1);
	return (0);
}

int	count_texture(t_data *data, int count)
{
	if (count != 6)
	{
		ft_error("Error\n Missing texture\n");
		free(data->texture);
		free(data->line);
		return (0);
	}
	return (1);
}

char	*get_map(t_data *data)
{
	char	*temp;

	data->map = ft_strdup("");
	while (data->line)
	{
		if (data->line[0] == '\n')
		{
			ft_error("Error\n Empty line\n");
			return (ft_free_readmap(data->line, data->map, -1), NULL);
		}
		temp = data->map;
		data->map = ft_strjoin(data->map, data->line);
		free(temp);
		free(data->line);
		data->line = get_next_line(data->fd);
	}
	return (data->map);
}

int	check_map_content(t_data *data, int count)
{
	data->map = get_map(data);
	if (!data->map)
		return (0);
	data->split_map = ft_split(data->map, '\n');
	if (!data->split_map)
		return (free(data->map), 0);
	free(data->map);
	if (!check_split_texture(data->split_texture, count)
		|| !check_fc_fromat(data->split_texture) || !check_duplicate(data)
		|| !check_lines(data->split_map)
		|| !surrounded_by_wall(data->split_map))
		return (ft_free_arr(data->split_map), 0);
	return (1);
}
