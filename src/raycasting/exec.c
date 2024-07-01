/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:28:47 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/01 13:22:36 by jsalaber         ###   ########.fr       */
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

	mlx = (t_mlx *)mlx_t;
	if (mlx->img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WW, WH);
	if (!mlx->img_ptr)
	{
		printf("Error: image not created\n");
		return (ft_exit(mlx), 1);
	}
	// raycasting(mlx, mlx->dat);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	return (0);
}

int	exit_game(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	ft_exit(mlx);
	exit(0);
}

int	exec(t_data *dat)
{
	t_mlx	mlx;

	if (WW > 2560 || WH > 1440 || FOV >= 180 || FOV <= 0)
		return (free_textures(dat->texture_list), ft_freemap(dat), 0);
	mlx.play = (t_player *)ft_calloc(1, sizeof(t_player));
	mlx.ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	mlx.texture = (t_texture *)ft_calloc(1, sizeof(t_texture));
	mlx.dat = dat;
	mlx.img_ptr = NULL;
	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		return (ft_exit(&mlx), 0);
	if (!load_all_textures(dat, &mlx))
		return (ft_exit(&mlx), 0);
	create_window(&mlx);
	mlx_key_hook(mlx.win_ptr, &key_pressed, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, &redraw_map, &mlx);
	mlx_loop(mlx.mlx_ptr);
	ft_exit(&mlx);
	return (0);
}
