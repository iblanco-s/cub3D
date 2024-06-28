/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:28:47 by jsalaber          #+#    #+#             */
/*   Updated: 2024/06/28 10:56:54 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	create_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_point, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_point, SW, SH);
	mlx_put_image_to_window(mlx->mlx_point, mlx->win, mlx->img, 0, 0);
}

int	exec(t_data *dat)
{
	t_mlx	mlx;

	if (SW >2560 || SH > 1440 || FOV >=180 || FOV <= 0)
		return (free_list(&dat->text), ft_freemap(dat), 0);
	mlx.play = (t_player *)ft_calloc(sizeof(t_player), 1);
	mlx.ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	mlx.texture = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	mlx.dat = dat;
	mlx.mlx_point = mlx_init(SW, SH, "Cub3D");
	if (!mlx.mlx_point)
		return (ft_exit(&mlx), 0);
	create_image(&mlx);
	mlx_loop(mlx.mlx);
	ft_exit(&mlx);
	return (0);
}