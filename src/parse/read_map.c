/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:03:55 by jsalaber          #+#    #+#             */
/*   Updated: 2024/06/12 12:37:33 by jsalaber         ###   ########.fr       */
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

int	read_map(char *argv, t_data *data, int *count)
{
	data->fd = open(argv, O_RDONLY);
	if (data->fd == -1)
		return (ft_error("Error: File not found\n"));
	data->line = get_next_line(data->fd);
	if (!data->line)
		return (ft_error("Error: File is empty\n"));
	data->texture = ft_strdup("");
	while(data->line && data->line[0] != '1' && data->line[0] != '32')
	{
		if(check_textures(data->line))
		{
			data->texture = ft_strjoin(data->texture, data->line);
			(*count)++;
		}
		free(data->line);
		data->line = get_next_line(data->fd);
	}
	if (!check_count_texture(data, *count))
		return (ft_free_readmap(NULL, NULL, data->fd), 0);
	data->split_texture = ft_split(data->texture, '\n');
	if (!data->split_texture)
		return (ft_free_readmap(NULL, data->texture, data->fd), 0);
	//comprobar contenido del mapa (0/1/2/N/S/W/E)
	//liberar memoria
}
