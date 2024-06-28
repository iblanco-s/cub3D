/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:12:33 by jsalaber          #+#    #+#             */
/*   Updated: 2024/06/28 11:08:12 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	free_list(t_text **tx)
{
	t_text	*tmp;

	tmp = *tx;
	while (tmp)
	{
		*tx = tmp->next;
		free(tmp->path);
		free(tmp->value);
		free(tmp);
		tmp = *tx;
	}
	free(*tx);
}

int	check_color_value(char **color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (ft_atoi(color[i]) < 0 || ft_atoi(color[i]) > 255)
			return (ft_free_arr(color), 0);
		i++;
	}
	return (ft_free_arr(color), 1);
}

void	save_color(t_text *text, t_data *data)
{
	if (!ft_strncmp(text->path, "F", 2))
	{
		data->floor = ft_split(text->value, ',');
		return ;
	}
	else if (!ft_strncmp(text->path, "C", 2))
	{
		data->ceiling = ft_split(text->value, ',');
		return ;
	}
}

int	check_color(t_data *data, t_text *mlx_texture)
{
	t_text	*tmp;

	data->ceiling = NULL;
	data->floor = NULL;
	tmp = mlx_texture;
	while (tmp)
	{
		if (!ft_strncmp(tmp->path, "F", 1) || !ft_strncmp(tmp->path, "C", 1))
		{
			if (!check_color_value(ft_split(tmp->value, ',')))
				return (ft_error("Error: Invalid color value\n"), 0);
			save_color(tmp, data);
		}
		tmp = tmp->next;
	}
	return (1);
}
