/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:28:47 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/01 11:39:47 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	create_window(t_mlx *mlx)
{
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WW, WH, "Cub3D");
	if (!mlx->win_ptr)
		ft_exit(mlx);
}

int	redraw_map(void *mlx_t)
{
	t_mlx	*mlx;

	mlx = mlx_t;
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WW, WH);
	// hook(mlx);
	// raycasting(mlx, mlx->dat);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	return (0);
}

int	exec(t_data *dat)
{
	t_mlx	mlx;

	if (WW > 2560 || WH > 1440 || FOV >= 180 || FOV <= 0)
		return (free_textures(dat->texture_list), ft_freemap(dat), 0);
	mlx.play = (t_player *)ft_calloc(sizeof(t_player), 1);
	mlx.ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	mlx.dat = dat;
	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		return (ft_exit(&mlx), 0);
	if (!load_all_textures(dat, &mlx))
		return (ft_exit(&mlx), 0);
	create_window(&mlx);
	//mlx_key_hook(mlx.win_ptr, 17, 0, hook, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, &redraw_map, &mlx);
	mlx_loop(mlx.mlx);
	ft_exit(&mlx);
	return (0);
}
