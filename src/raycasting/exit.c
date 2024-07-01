/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:46:36 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/01 11:34:41 by jsalaber         ###   ########.fr       */
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

void	ft_exit(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	free_textures(mlx->dat->texture_list);
	ft_freemap(mlx->dat);
	free(mlx->ray);
	free(mlx->play);
	free(mlx->mlx_ptr);
	ft_putendl_fd("Cub3D closed", 1);
	exit(0);
}
