/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:03:55 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/16 17:34:44 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	ft_free_readmap(char *line, char *texture, int fd)
{
	if (texture)
		free(texture);
	if (line)
		free(line);
	if (fd > 0)
		close(fd);
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*ft_free_and_join(char *str1, char *str2)
{
	char	*temp;

	temp = ft_strjoin(str1, str2);
	free(str1);
	return (temp);
}

int	read_map(char *argv, t_data *data, int *count)
{
	data->fd = open(argv, O_RDONLY);
	if (data->fd == -1)
		return (ft_error("Error\nFile not found\n"));
	data->line = get_next_line(data->fd);
	if (!data->line)
		return (ft_error("Error\nFile is empty\n"));
	data->texture = ft_strdup("");
	while (data->line && data->line[0] != '1' && data->line[0] != ' ')
	{
		if (check_textures(data->line))
		{
			data->texture = ft_free_and_join(data->texture, data->line);
			(*count)++;
		}
		free(data->line);
		data->line = get_next_line(data->fd);
	}
	if (!count_texture(data, *count))
		return (ft_free_readmap(NULL, NULL, data->fd), 0);
	data->split_texture = ft_split(data->texture, '\n');
	if (!data->split_texture)
		return (ft_free_readmap(NULL, data->texture, data->fd), 0);
	if (!check_map_content(data, *count))
		return (ft_free_readmap(data->line, data->texture, data->fd), 0);
	return (ft_free_readmap(data->line, data->texture, data->fd), 1);
}

void	ft_freemap(t_data *data)
{
	ft_free_arr(data->split_texture);
	ft_free_arr(data->split_map);
	ft_free_arr(data->map_copy);
	if (data->ceiling)
		ft_free_arr(data->ceiling);
	if (data->floor)
		ft_free_arr(data->floor);
}
