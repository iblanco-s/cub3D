/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:28:47 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/05 12:57:28 by jsalaber         ###   ########.fr       */
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
	// if (mlx->img_ptr)
	// 	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	// mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WW, WH);
	// if (!mlx->img_ptr)
	// {
	// 	printf("Error: image not created\n");
	// 	return (ft_exit(mlx), 1);
	// }
	execute_player_move(mlx, 0, 0);
	raycasting(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	return (0);
}

int	exit_game(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(0);
	return (0);
}

void	locate_player(t_mlx *mlx)
{
	int		p;

	p = mlx->dat->split_map[mlx->dat->player_y][mlx->dat->player_x];
	if (p == 'E')
		mlx->play->playr_dir = 0;
	if (p == 'S')
		mlx->play->playr_dir = PI / 2;
	if (p == 'W')
		mlx->play->playr_dir = PI;
	if (p == 'N')
		mlx->play->playr_dir = 3 * PI / 2;
	mlx->play->playr_x = (mlx->dat->player_x * TILE_SIZE) + TILE_SIZE / 2;
	mlx->play->playr_y = (mlx->dat->player_y * TILE_SIZE) + TILE_SIZE / 2;
	mlx->play->fov_rad = (FOV * PI) / 180;
}

int	exec(t_data *dat)
{
	t_mlx	mlx;

	if (WW > 2560 || WH > 1440 || FOV >= 180 || FOV <= 0)
		return (free_textures(dat->texture_list), ft_freemap(dat), 0);
	mlx.play = (t_player *)ft_calloc(1, sizeof(t_player));
	mlx.ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	mlx.texture = (t_texture *)ft_calloc(1, sizeof(t_texture));
	mlx.tex = (t_tex *)ft_calloc(1, sizeof(t_tex));
	mlx.dat = dat;
	mlx.img_ptr = NULL;
	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		return (ft_exit(&mlx), 0);
	if (!load_all_textures(dat, &mlx))
		return (ft_exit(&mlx), 0);
	create_window(&mlx);
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, WW, WH);
	mlx.img_data = mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.size_line, &mlx.endian);
	locate_player(&mlx);
	mlx_hook(mlx.win_ptr, 17, 0, exit_game, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1L<<0, key_pressed, &mlx);
	mlx_hook(mlx.win_ptr, 3, 1L<<1, hanlde_key_release, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, &redraw_map, &mlx);
	mlx_loop(mlx.mlx_ptr);
	ft_exit(&mlx);
	return (0);
}
