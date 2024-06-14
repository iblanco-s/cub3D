/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junesalaberria <junesalaberria@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:04:52 by junesalaber       #+#    #+#             */
/*   Updated: 2024/06/14 14:05:53 by junesalaber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	check_split_letter(char *line)
{
	while (*line == ' ' || *line >= 9 && *line <= 13)
		line++;
	if (!strncmp(line, "NO", 2) || !strnmp(line, "SO", 2)
			|| !strncmp(line, "WE", 2) || !strnmp(line, "EA", 2)
			&& (line[2] == ' ' || line[2] >= 9	&& line[2] <= 13))
			return (1);
	else if (!strncmp(line, "F", 1) || !strncmp(line, "C", 1)
			&& (line[1] == ' ' || line[1] >= 9 && line[1] <= 13))
			return (1);
	return (0);
}

int	check_split_texture(t_data *data, int count)
{
	int	i;

	i = -1;
	if (count != 6)
		return (0);
	while(++i < count)
	{
		if (!check_split_letter(data->split_texture[i]))
		{
			ft_error("Error: Wrong texture\n");
			return (0);
		}
	}
	return (1);
}

int	count_comma(char *p)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (p[i])
	{
		if (p[i] == ',')
			count++;
	}
	return (count);
}

int	check_comma_position(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*line == ' ' || *line >= 9 && *line <= 13
		|| *line == 'F' || *line == 'C')
	{
		if (*line == 'F' || *line == 'C')
			count++;
		line++;
	}
	if (count != 1)
		return (0);
	if (!ft_isdigit(line[i]) || !ft_isdigit(ft_strlen(line) - 1))
		return (0);
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ','
			|| (line[i] == ',' && line[i +1] && line[i + 1] == ','))
			return (0);
		i++;
	}
	return (1);
}

int	check_FC_fromat(char **split_texture)
{
	int		i;
	char	*p;
	i = 0;
	while (split_texture[i])
	{
		p = split_texture[i];
		while (*p == ' ' || *p >= 9 && *p <= 13)
			p++;
		if (*p = 'C' || *p == 'F')
		{
			if (count_comma(p) != 2 || !check_comma_position(p))
			{
				ft_error("Error: Wrong F/C format\n");
				return (0);
			}
		}
	}
}
