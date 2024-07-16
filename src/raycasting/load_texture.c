/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:31:07 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/16 09:55:17 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

bool	valid_texture(int width, int height)
{
	if (width != TILE_SIZE || height != TILE_SIZE)
	{
		ft_error("Error\nTexture size is correct\n");
		return (false);
	}
	return (true);
}

int	load_texture(t_text *text)
{
	t_text			*temp;
	mlx_texture_t	*texture;

	temp = text;
	while (temp)
	{
		if (!ft_strncmp(temp->value, "NO", 2)
			|| !ft_strncmp(temp->value, "EA", 2)
			|| !ft_strncmp(temp->value, "SO", 2)
			|| !ft_strncmp(temp->value, "WE", 2))
		{
			texture = mlx_load_png(temp->path);
			if (!texture)
				return (0);
			mlx_delete_texture(texture);
		}
		temp = temp->next;
	}
	return (1);
}

int	load_all_textures(t_tex *tex, t_text *texture)
{
	t_text	*temp;

	temp = texture;
	if (!valid_texture(TILE_SIZE, TILE_SIZE))
		return (0);
	if (!load_texture(texture))
		return (0);
	while (temp)
	{
		if (!ft_strncmp(temp->value, "NO", 2))
			tex->no = mlx_load_png(temp->path);
		else if (!ft_strncmp(temp->value, "SO", 2))
			tex->so = mlx_load_png(temp->path);
		else if (!ft_strncmp(temp->value, "WE", 2))
			tex->we = mlx_load_png(temp->path);
		else if (!ft_strncmp(temp->value, "EA", 2))
			tex->ea = mlx_load_png(temp->path);
		temp = temp->next;
	}
	return (1);
}
