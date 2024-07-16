/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:54:07 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/16 10:03:38 by jsalaber         ###   ########.fr       */
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

float	normalize_angle(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

mlx_texture_t	*get_texture(t_mlx *mlx, int flag)
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
			return (mlx->tex->no);
		else
			return (mlx->tex->so);
	}
}

double	get_impact_point(mlx_texture_t *texture, t_mlx *mlx)
{
	double	impact_point;

	if (mlx->ray->flag == 1)
	{
		impact_point = (int)fmodf((mlx->ray->wall_h_x
					* (texture->width / TILE_SIZE)), texture->width);
	}
	else if (mlx->ray->flag == 0)
	{
		impact_point = (int)fmodf((mlx->ray->wall_v_y
					* (texture->width / TILE_SIZE)), texture->width);
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
