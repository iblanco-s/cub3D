/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:31:07 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/03 16:16:25 by codespace        ###   ########.fr       */
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

bool	load_texture(t_mlx *mlx, t_text *tx)
{
	int	width;
	int	height;
	t_img *img_ptr;

	if (!ft_strncmp(tx->value, "C", 1) || !ft_strncmp(tx->value, "F", 1))
		return (true);
	img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, tx->path, &width, &height);
	if (!img_ptr)
	{		//habria que hacer algo mas?
		return (ft_error("Error: Texture not found\n"), false);
	}
	if (!valid_texture(width, height))
	{
		mlx_destroy_image(mlx->mlx_ptr, img_ptr);
		return (false);
	}
	if (!ft_strncmp(tx->value, "NO", 2))
		mlx->tex->no = img_ptr;
	else if (!ft_strncmp(tx->value, "SO", 2))
		mlx->tex->so = img_ptr;
	else if (!ft_strncmp(tx->value, "WE", 2))
		mlx->tex->we = img_ptr;
	else if (!ft_strncmp(tx->value, "EA", 2))
		mlx->tex->ea = img_ptr;
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
		if (!load_texture(mlx, cur_texture))
			return (free_textures(data->texture_list), ft_freemap(data), false); //fretextures funciona con el coidgo nuevo?
		cur_texture = cur_texture->next;
	}
	return (true);
}
