/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junesalaberria <junesalaberria@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:01:50 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/12 11:09:38 by junesalaber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	rotate_player(t_mlx *mlx, int flag)
{
	if (flag == 1)
	{
		mlx->play->playr_dir += ROTATION_SPEED;
		if (mlx->play->playr_dir > 2 * PI)
			mlx->play->playr_dir -= 2 * PI;
	}
	else
	{
		mlx->play->playr_dir -= ROTATION_SPEED;
		if (mlx->play->playr_dir < 0)
			mlx->play->playr_dir += 2 * PI;
	}
}

void	move_player(t_mlx *mlx, double move_x, double move_y)
{
	int	new_x;
	int	new_y;
	int	map_new_x;
	int	map_new_y;

	new_x = roundf(mlx->play->playr_x + move_x);
	new_y = roundf(mlx->play->playr_y + move_y);
	map_new_x = (new_x / TILE_SIZE);
	map_new_y = (new_y / TILE_SIZE);
	if (mlx->dat->split_map[map_new_y][map_new_x] != '1'
		&& mlx->dat->split_map[map_new_y][mlx->play->playr_x / \
		TILE_SIZE != '1']
		&& mlx->dat->split_map[mlx->play->playr_y / \
		TILE_SIZE][map_new_x] != '1')
	{
		mlx->play->playr_x = new_x;
		mlx->play->playr_y = new_y;
	}
	debug_print("map_new_x: %d\n", map_new_x);
	debug_print("map_new_y: %d\n", map_new_y);
	debug_print("new_x: %d\n", new_x);
	debug_print("new_y: %d\n", new_y);
}

void	execute_player_move(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->play->rotate == 1)
		rotate_player(mlx, 1);
	if (mlx->play->rotate == -1)
		rotate_player(mlx, 0);
	if (mlx->play->h_move == 1)
	{
		move_x = -sin(mlx->play->playr_dir) * MOVE_SPEED;
		move_y = cos(mlx->play->playr_dir) * MOVE_SPEED;
	}
	if (mlx->play->h_move == -1)
	{
		move_x = sin(mlx->play->playr_dir) * MOVE_SPEED;
		move_y = -cos(mlx->play->playr_dir) * MOVE_SPEED;
	}
	if (mlx->play->v_move == 1)
	{
		move_x = cos(mlx->play->playr_dir) * MOVE_SPEED;
		move_y = sin(mlx->play->playr_dir) * MOVE_SPEED;
	}
	if (mlx->play->v_move == -1)
	{
		move_x = -cos(mlx->play->playr_dir) * MOVE_SPEED;
		move_y = -sin(mlx->play->playr_dir) * MOVE_SPEED;
	}
	move_player(mlx, move_x, move_y);
	//debug_print("Player moved to: (%f, %f)\n", mlx->play->playr_x, mlx->play->playr_y);
    //debug_print("Player direction: %f\n", mlx->play->playr_dir);
}

void	hanlde_key_release(mlx_key_data_t keycode, t_mlx *mlx)
{
	if (keycode.key == MLX_KEY_D && keycode.action == MLX_RELEASE)
		mlx->play->h_move = 0;
	else if (keycode.key == MLX_KEY_A && keycode.action == MLX_RELEASE)
		mlx->play->h_move = 0;
	else if (keycode.key == MLX_KEY_W && keycode.action == MLX_RELEASE)
		mlx->play->v_move = 0;
	else if (keycode.key == MLX_KEY_S && keycode.action == MLX_RELEASE)
		mlx->play->v_move = 0;
	else if (keycode.key == MLX_KEY_LEFT && keycode.action == MLX_RELEASE)
		mlx->play->rotate = 0;
	else if (keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_RELEASE)
		mlx->play->rotate = 0;
}

void	key_pressed(mlx_key_data_t keycode, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (keycode.key == MLX_KEY_ESCAPE && (keycode.action == MLX_PRESS
		|| keycode.action == MLX_REPEAT))
		ft_exit(mlx);
	else if (keycode.key == MLX_KEY_D && keycode.action == MLX_PRESS)
		mlx->play->h_move = 1;
	else if (keycode.key == MLX_KEY_A && keycode.action == MLX_PRESS)
		mlx->play->h_move = -1;
	else if (keycode.key == MLX_KEY_W && keycode.action == MLX_PRESS)
		mlx->play->v_move = 1;
	else if (keycode.key == MLX_KEY_S && keycode.action == MLX_PRESS)
		mlx->play->v_move = -1;
	else if (keycode.key == MLX_KEY_LEFT && keycode.action == MLX_PRESS)
		mlx->play->rotate = -1;
	else if (keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_PRESS)
		mlx->play->rotate = 1;
	hanlde_key_release(keycode, mlx);
}
