/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junesalaberria <junesalaberria@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:03:40 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/12 16:04:52 by junesalaber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	map_len(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	line_maxlen(char **map)
{
	int	i;
	int	max_len;

	i = 0;
	max_len = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) > max_len)
			max_len = ft_strlen(map[i]);
		i++;
	}
	return (max_len);
}

char	*adjust_line(char *line, int max_len)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = ft_calloc(sizeof(char), (max_len + 1));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < max_len)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

int	manage_spaces_width(char **map)
{
	int	x;
	int	y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] != '1' && map[x][y] != ' ')
			{
				if (map[x][y - 1] == ' ' || map[x][y + 1] == ' ')
				{
					ft_error("Error\n Invalid map (spaces in width)");
					return (0);
				}
			}
			y++;
		}
		x++;
	}
	return (1);
}

int	manage_spaces_height(char **map)
{
	int	x;
	int	y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] != '1' && map[x][y] != ' ')
			{
				if (map[x - 1][y] == ' ' || map[x + 1][y] == ' ')
				{
					ft_error("Error\n Invalid map (spaces in height)");
					return (0);
				}
			}
			y++;
		}
		x++;
	}
	return (1);
}
