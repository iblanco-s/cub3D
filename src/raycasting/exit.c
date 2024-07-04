/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:46:36 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/04 12:58:34 by iblanco-         ###   ########.fr       */
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

void	free_tex(void *mlx_ptr, t_tex *tex)
{
	if (tex->no)
		mlx_destroy_image(mlx_ptr, tex->no);
	if (tex->so)
		mlx_destroy_image(mlx_ptr, tex->so);
	if (tex->we)
		mlx_destroy_image(mlx_ptr, tex->we);
	if (tex->ea)
		mlx_destroy_image(mlx_ptr, tex->ea);
	free(tex);
}

void	ft_exit(t_mlx *mlx)
{
	if (mlx->img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	if (mlx->win_ptr)
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->dat)
	{
		free_textures(mlx->dat->texture_list);
		ft_freemap(mlx->dat);
	}
	free(mlx->ray);
	free(mlx->play);
	free(mlx->texture);
	free_tex(mlx->mlx_ptr, mlx->tex);
	if (mlx->mlx_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	ft_putendl_fd("Cub3D closed", 1);
	exit(0);
}
