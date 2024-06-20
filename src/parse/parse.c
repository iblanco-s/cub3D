/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:52:44 by jsalaber          #+#    #+#             */
/*   Updated: 2024/06/20 12:44:13 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	ft_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (1);
}

void	get_player_position(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map_copy[i])
	{
		j = 0;
		while (data->map_copy[i][j])
		{
			if (data->map_copy[i][j] == 'N' || data->map_copy[i][j] == 'S'
				|| data->map_copy[i][j] == 'W' || data->map_copy[i][j] == 'E')
			{
				data->player_x = j;
				data->player_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	get_lines_column(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->split_map[i])
	{
		j = 0;
		while (data->split_map[i][j])
			j++;
		if (j > data->map_column)
			data->map_column = j;
		i++;
	}
	data->map_lines = i;
}

int	parse(int argc, char **argv, t_data *data)
{
	int	count;

	if (argc != 2 || !check_extension(argv[1]))
	{
		ft_error("Error: Wrong argument\n");
		exit(0);
	}
	count = 0;
	if (!read_map(argv[1], data, &count))
		return (0);
	if (!map_size(data))
		return (0);
	get_player_position(data);
	get_lines_column(data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	parse(argc, argv, &data);
	raycasting(data);
	return (0);
}
