/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:06:49 by junesalaber       #+#    #+#             */
/*   Updated: 2024/07/16 17:05:03 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	check_column_round_by_wall(char *line)
{
	while (*line == ' ' || (*line >= 9 && *line <= 13))
		line++;
	if (*line != '1' || line[ft_strlen(line) - 1] != '1')
		return (0);
	return (1);
}

int	valid_map(char *line, int *count)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] != '1' && line[i] != ' '
				&& line[i] != '0' && line[i] != '\n')
			&& !(line[i] == 'W' || line[i] == 'E'
				|| line[i] == 'N' || line[i] == 'S'))
			return (0);
		else if (line[i] == 'W' || line[i] == 'E'
			|| line[i] == 'N' || line[i] == 'S')
			(*count)++;
		i++;
	}
	return (1);
}

void	ft_free_data(t_data *data)
{
	int	i;

	i = 0;
	if (!data->split_texture)
		return ;
	while (data->split_texture[i])
	{
		free(data->split_texture[i]);
		i++;
	}
}
