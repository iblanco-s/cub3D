/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:31:07 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/01 12:32:26 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

bool	valid_texture(int width, int height)
{
	if (width != TILE_SIZE || height != TILE_SIZE)
	{
		ft_error("Error: Texture size is correct\n");
		return (false);
	}
	return (true);
}

bool	load_texture(t_texture *texture, void *mlx_ptr, t_text *tx)
{
	int	width;
	int	height;

	texture->img = NULL;
	texture->created = false;
	if (!ft_strncmp(tx->value, "C", 1) || !ft_strncmp(tx->value, "F", 1))
	{
		texture->created = true;
		return (true);
	}
	texture->img = mlx_xpm_file_to_image(mlx_ptr, tx->path, &width, &height);
	texture->created = true;
	if (!texture->img)
	{
		texture->created = false;
		return (ft_error("Error: Texture not found\n"), false);
	}
	if (!valid_texture(width, height))
	{
		mlx_destroy_image(mlx_ptr, texture->img);
		texture->img = NULL;
		texture->created = false;
		return (false);
	}
	return (true);
}

bool	load_all_textures(t_data *data, t_mlx *mlx)
{
	t_text	*cur_texture;

	cur_texture = data->texture_list;
	while (cur_texture)
	{
		if (cur_texture->texture == NULL)
			cur_texture->texture = mlx->texture;
		if (!load_texture(cur_texture->texture, mlx->mlx_ptr, cur_texture))
			return (free_textures(data->texture_list), ft_freemap(data), false);
		cur_texture = cur_texture->next;
	}
	return (true);
}
