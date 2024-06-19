/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:29:04 by jsalaber          #+#    #+#             */
/*   Updated: 2024/06/19 10:10:38 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	map_size(t_data *data)
{
	int	i;
	int	max_len;

	i = 0;
	max_len = line_maxlen(data->split_map);
	data->map_copy = ft_calloc(sizeof(char *), (map_len(data->split_map) + 1));
	if (!data->map_copy)
		return (0);
	while (data->split_map[i])
	{
		if (max_len == ft_strlen(data->split_map[i]))
			data->map_copy[i] = ft_strdup(data->split_map[i]);
		else
			data->map_copy[i] = adjust_line(data->split_map[i], max_len);
		i++;
	}
	data->map_copy[i] = NULL;
	data->map_height = map_len(data->map_copy);
	data->map_width = ft_strlen(data->map_copy[0]);
	if (!manage_spaces_width(data->map_copy)
		|| !manage_spaces_height(data->map_copy))
		return (ft_free_arr(data->map_copy), ft_free_arr(data->split_map),
			ft_free_arr(data->split_texture), 0);
	return (1);
}
