/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:54:07 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/03 15:28:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	reverse_bytes(int num)
{
	unsigned int	a;

	a = 0;
	a |= (num & 0xFF) << 24;
	a |= (num & 0xFF00) << 8;
	a |= (num & 0xFF0000) >> 8;
	a |= (num & 0xFF000000) >> 24;
	return (a);
}

float normalize_angle(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	*get_texture(t_mlx *mlx, int flag)
{
	mlx->ray->ray_angle = normalize_angle(mlx->ray->ray_angle);
	if (flag == 0)
	{
		if (mlx->ray->ray_angle > PI / 2 && mlx->ray->ray_angle < 3 * PI / 2)
			return (mlx->tex->ea);
		else
			return (mlx->tex->we);
	}
	else
	{
		if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < PI)
			return (mlx->tex->so);
		else
			return (mlx->tex->no);
	}
}

double	get_impact_point(t_img *img, t_mlx *mlx)
{
	double	impact_point;
	double	temp;
	
	if (mlx->ray->flag == 1)
	{
		temp = mlx->ray->wall_h_x * (img->width / TILE_SIZE);
		impact_point = temp - (int)(temp / img->width) * img->width;
	}
	else
	{
		temp = mlx->ray->wall_v_y * (img->width / TILE_SIZE);
		impact_point = temp - (int)(temp / img->width) * img->width;
	}
	return (impact_point);
}

int	unit_circle(float angle, char axis)
{
	if (axis == 'x')
	{
		if (angle > 0 && angle < PI)
			return (1);
	}
	else if (axis == 'y')
	{
		if (angle > PI / 2 && angle < 3 * PI / 2)
			return (1);
	}
	return (0);
}
