/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:01:50 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/04 14:11:56 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	rotate_player(t_mlx *mlx, bool flag)
{
	if (flag)
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

	new_x = (int)(mlx->play->playr_x + move_x + 0.5);
	new_y = (int)(mlx->play->playr_y + move_y + 0.5);
	map_new_x = (new_x / TILE_SIZE);
	map_new_y = (new_y / TILE_SIZE);
	if (mlx->dat->split_map[map_new_y][map_new_x] != '1'
		&& mlx->dat->map_copy[map_new_y][(int)mlx->play->playr_x / \
		TILE_SIZE != '1']
		&& mlx->dat->map_copy[(int)mlx->play->playr_y / \
		TILE_SIZE][map_new_x] != '1')
	{
		mlx->play->playr_x = new_x;
		mlx->play->playr_y = new_y;
	}
}

void	execute_player_move(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->play->rotate == 1)
		rotate_player(mlx, true);
	if (mlx->play->rotate == -1)
		rotate_player(mlx, false);
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
}

void	hanlde_key_release(int keycode, t_mlx *mlx)
{
	if (keycode == D || keycode == A)
		mlx->play->h_move = 0;
	else if (keycode == W || keycode == S)
		mlx->play->v_move = 0;
	else if (keycode == LEFT || keycode == RIGHT)
		mlx->play->rotate = 0;
}

int	key_pressed(int keycode, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (keycode == ESC)
		ft_exit(mlx);
	else if (keycode == D)
		mlx->play->h_move = 1;
	else if (keycode == A)
		mlx->play->h_move = -1;
	else if (keycode == W)
		mlx->play->v_move = 1;
	else if (keycode == S)
		mlx->play->v_move = -1;
	else if (keycode == LEFT)
		mlx->play->rotate = -1;
	else if (keycode == RIGHT)
		mlx->play->rotate = 1;
	// hanlde_key_release(keycode, mlx);
	return (0);
}
