/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:00:09 by jsalaber          #+#    #+#             */
/*   Updated: 2024/06/12 12:29:31 by jsalaber         ###   ########.fr       */
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
	while (*line == ' ' || *line >= 9 && *line <= 13)
		line++;
	if ((!strncmp(line, "NO", 2) || !strnmp(line, "SO", 2)
			|| !strncmp(line, "WE", 2) || !strnmp(line, "EA", 2))
		|| !strncmp(line, "F", 1) || !strncmp(line, "C", 1))
		return (1);
	return (0);
}

int	check_count_texture(t_data *data, int count)
{
	if (count != 6)
	{
		ft_error("Error: Missing texture\n");
		free(data->texture);
		free(data->line);
		return (0);
	}
	return (1);
}
