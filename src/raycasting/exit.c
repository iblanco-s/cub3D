/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:46:36 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/15 13:39:22 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	free_textures(t_text *texture_list)
{
	t_text	*tmp;

	while (texture_list)
	{
		tmp = texture_list;
		texture_list = texture_list->next;
		free(tmp->value);
		free(tmp->path);
		free(tmp);
	}
}

void	free_tex(t_tex *tex)
{
	if (tex->no)
		mlx_delete_texture(tex->no);
	if (tex->so)
		mlx_delete_texture(tex->so);
	if (tex->we)
		mlx_delete_texture(tex->we);
	if (tex->ea)
		mlx_delete_texture(tex->ea);
}

void	ft_exit(t_mlx *mlx)
{
	free_textures(mlx->dat->texture_list);
	ft_freemap(mlx->dat);
	free(mlx->ray);
	free(mlx->play);
	free_tex(mlx->tex);
	free(mlx->tex);
	mlx_terminate(mlx->mlx_ptr);
	ft_putendl_fd("Cub3D closed", 1);
	exit(0);
}
