/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:52:14 by junesalaber       #+#    #+#             */
/*   Updated: 2024/07/16 09:54:48 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	check_duplicate(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->split_texture[i])
	{
		j = i + 1;
		while (data->split_texture[j])
		{
			if (!ft_strncmp(data->split_texture[i], data->split_texture[j], 2))
				return (ft_error("Error\nDuplicate texture\n"), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_line_round_by_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*get_last_line(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (map[i - 1]);
}

int	check_lines(char **map)
{
	if (!map[0])
		return (ft_error("Error\nEmpty map\n"), 0);
	if (!check_line_round_by_wall(map[0])
		|| !check_line_round_by_wall(get_last_line(map)))
		return (ft_error("Error\nMap not surrounded by walls\n"), 0);
	return (1);
}

int	surrounded_by_wall(char **map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		if (!check_column_round_by_wall(map[i])
			|| !valid_map(map[i], &count) || count > 1)
			return (ft_error("Error\nInvalid map\n"), 0);
		i++;
	}
	if (count == 0)
		return (ft_error("Error\nMissing character on the map\n"), 0);
	return (1);
}
