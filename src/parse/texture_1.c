/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:58:13 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/16 15:55:48 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	get_index(char *line, int i)
{
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	return (i);
}

t_text	*new_texture(char *line)
{
	t_text	*list;

	list = (t_text *)ft_calloc(sizeof(t_text), 1);
	if (!list)
		return (NULL);
	while (*line == ' ' || (*line >= 9 && *line <= 13))
		line++;
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
	{
		list->value = ft_substr(line, 0, 2);
		list->path = ft_substr(line, get_index(line, 2), ft_strlen(line));
	}
	else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
	{
		list->value = ft_substr(line, 0, 1);
		list->path = ft_substr(line, get_index(line, 1), ft_strlen(line));
	}
	list->next = NULL;
	return (list);
}

void	last_texture(t_text **mlx_texture, t_text *new)
{
	t_text	*tmp;

	tmp = *mlx_texture;
	if (*mlx_texture == NULL)
	{
		*mlx_texture = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_check_texture(char *file)
{
	int	len;
	int	fd;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".png", 4) != 0)
	{
		ft_putendl_fd("Error\nInvalid file extension. Must be '.png'", 2);
		return (0);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error\nFile does not exist or is not accessible", 2);
		return (0);
	}
	close(fd);
	return (1);
}

int	ft_list_texture(t_data *data, t_text **mlx_texture)
{
	int		i;
	t_text	*new;

	i = 0;
	while (data->split_texture[i])
	{
		new = new_texture(data->split_texture[i++]);
		if (!new)
			return (0);
		if (i < 5 && !ft_check_texture(new->path))
			return (free(new->path), free(new->value),
				free(new), 0);
		last_texture(mlx_texture, new);
	}
	return (1);
}
