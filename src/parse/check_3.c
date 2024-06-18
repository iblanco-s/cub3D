/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:06:49 by junesalaber       #+#    #+#             */
/*   Updated: 2024/06/18 13:04:17 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	check_column_round_by_wall(char *line)
{
	while (*line == ' ' || (*line >= 9 && *line <= 13))
		line++;
	printf("line = %s\n", line);
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
