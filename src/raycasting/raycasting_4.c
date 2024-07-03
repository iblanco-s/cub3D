/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:02:42 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/03 10:40:31 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	hit_wall(t_mlx *mlx, float x, float y)
{
	int		map_x;
	int		map_y;

	if (x < 0 || y < 0)
		return (0);
	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);

	if (map_x >= mlx->dat->map_width || map_y >= mlx->dat->map_height)
		return (0);
	if (mlx->dat->split_map[map_y] && map_x < (int)ft_strlen(mlx->dat->split_map[map_y]))
	{
		if (mlx->dat->split_map[map_y][map_x] == '1')
			return (0);
	}
	return (1);
}

int	check_inter(float angle, float *inter, float *step, int flag)
{
	if (flag)
	{
		if (angle > 0 && angle < PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (angle > PI / 2 && angle < 3 * PI / 2)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

float	check_h_inter(t_mlx *mlx, float angle)
{
	float	inter_x;
	float	inter_y;
	float	step_x;
	float	step_y;
	int		flag;
	float	dx;
	float	dy;

	step_y = TILE_SIZE;
	step_x = TILE_SIZE / tan(angle);
	inter_y = ((int)(mlx->play->playr_y / TILE_SIZE)) * TILE_SIZE;
	flag = check_inter(angle, &inter_y, &step_y, 1);
	inter_x = mlx->play->playr_x + (inter_y - mlx->play->playr_y) / tan(angle);
	if ((unit_circle(angle, 'y') && step_x < 0) || (!unit_circle(angle, 'y') && step_x > 0))
		step_x *= -1;
	while (hit_wall(mlx, inter_x, inter_y - flag))
	{
		inter_x += step_x;
		inter_y += step_y;
	}
	mlx->ray->wall_h_x = inter_x;
	mlx->ray->wall_h_y = inter_y;
	dx = inter_x - mlx->play->playr_x;
	dy = inter_y - mlx->play->playr_y;
	return (sqrt(dx * dx + dy * dy));
}

float	check_v_inter(t_mlx *mlx, float angle)
{
	float	inter_x;
	float	inter_y;
	float	step_x;
	float	step_y;
	int		flag;
	float	dx;
	float	dy;

	step_x = TILE_SIZE;
	step_y = TILE_SIZE * tan(angle);
	inter_x = ((int)(mlx->play->playr_x / TILE_SIZE)) * TILE_SIZE;
	flag = check_inter(angle, &inter_x, &step_x, 0);
	inter_y = mlx->play->playr_y + (inter_x - mlx->play->playr_x) * tan(angle);
	if ((unit_circle(angle, 'x') && step_y < 0) || (!unit_circle(angle, 'x') && step_y > 0))
		step_y *= -1;
	while (hit_wall(mlx, inter_x - flag, inter_y))
	{
		inter_x += step_x;
		inter_y += step_y;
	}
	mlx->ray->wall_v_x = inter_x;
	mlx->ray->wall_v_y = inter_y;
	dx = inter_x - mlx->play->playr_x;
	dy = inter_y - mlx->play->playr_y;
	return (sqrt(dx * dx + dy * dy));
}

void	raycasting(t_mlx *mlx)
{
	double	inter_h;
	double	inter_v;
	int		ray;

	ray = 0;
	mlx->ray->ray_angle = mlx->play->playr_dir - mlx->play->fov_rad / 2;
	while (ray < WW)
	{
		mlx->ray->flag = 0;
		inter_h = check_h_inter(mlx, mlx->ray->ray_angle);
		inter_v = check_v_inter(mlx, mlx->ray->ray_angle);
		if (inter_v <= inter_h)
			mlx->ray->distance = inter_v;
		else
		{
			mlx->ray->distance = inter_h;
			mlx->ray->flag = 1;	
		}
		draw_wall_segment(mlx, ray);
		ray++;
		mlx->ray->ray_angle += mlx->play->fov_rad / WW;
	}	
}
