/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:28:47 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/15 09:41:26 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void debug_print(const char *format, ...) {
    if (DEBUG) {
        va_list args;
        va_start(args, format);
        printf("[DEBUG] ");
        vprintf(format, args);
        va_end(args);
    }
}


void	redraw_map(void *mlx_t)
{
	t_mlx	*mlx;

	mlx = mlx_t;
	mlx_delete_image(mlx->mlx_ptr, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_ptr, WW, WH);
	execute_player_move(mlx, 0, 0);
	raycasting(mlx);
	draw_minimap(mlx);
	mlx_image_to_window(mlx->mlx_ptr, mlx->img, 0, 0);
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

void mouse_moved(void *param)
{
    t_mlx *mlx;
    int mouse_x;
	int mouse_y;
	int	delta_x;
    float sensitivity;

	sensitivity = 0.01f;
    mlx = param;
    mlx_get_mouse_pos(mlx->mlx_ptr, &mouse_x, &mouse_y);
    delta_x = mouse_x - (WW / 2);
    mlx->play->playr_dir += sensitivity * delta_x;
    mlx->play->playr_dir = normalize_angle(mlx->play->playr_dir);
    mlx_set_mouse_pos(mlx->mlx_ptr, WW / 2, WH / 2);
}


int	exec(t_data *dat)
{
	t_mlx	mlx;

	if (WW > 2560 || WH > 1440 || FOV >= 180 || FOV <= 0)
		return (free_textures(dat->texture_list), ft_freemap(dat), 0);
	mlx.play = (t_player *)ft_calloc(1, sizeof(t_player));
	mlx.ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	mlx.tex = (t_tex *)ft_calloc(1, sizeof(t_tex));
	mlx.dat = dat;
	mlx.mlx_ptr = mlx_init(WW, WH, "Cub3D", false);
	if (!mlx.mlx_ptr)
		return (ft_exit(&mlx), 0);
	if (!load_all_textures(mlx.tex, dat->texture_list))
		return (ft_exit(&mlx), 0);
	locate_player(&mlx);
	mlx_key_hook(mlx.mlx_ptr, &key_pressed, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, &redraw_map, &mlx);
	mlx_set_cursor_mode(mlx.mlx_ptr, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(mlx.mlx_ptr, (void *)&mouse_moved, &mlx);
	// debug_print("Initial player position: (%f, %f)\n", mlx.play->playr_x, mlx.play->playr_y);
    // debug_print("Initial player direction: %f\n", mlx.play->playr_dir);
    // debug_print("FOV: %f\n", mlx.play->fov_rad);
	mlx_loop(mlx.mlx_ptr);
	ft_exit(&mlx);
	return (0);
}
