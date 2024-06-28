/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:46:36 by jsalaber          #+#    #+#             */
/*   Updated: 2024/06/28 11:02:49 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	ft_delete_texture(t_texture *texture)
{
	if (texture->no)
		free(texture->no);
	if (texture->so)
		free(texture->so);
	if (texture->we)
		free(texture->we);
	if (texture->ea)
		free(texture->ea);
}

void ft_exit(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_point, mlx->img);
	mlx_clear_window(mlx->mlx_point, mlx->win);
	free_list(&mlx->dat->text);
	ft_freemap(mlx->dat);
	ft_delete_texture(mlx->texture);
	free(mlx->ray);
	free(mlx->play);
	free(mlx->texture);
	free(mlx->mlx_point);
	ft_putendl_fd("Cub3D closed", 1);
	exit(0);
}