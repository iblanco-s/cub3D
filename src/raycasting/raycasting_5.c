/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:23:14 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/16 10:55:58 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	wall_params(t_mlx *mlx, int u_pix, double wall_height, t_param *params)
{
	params->texture = get_texture(mlx, mlx->ray->flag);
	params->scale = (double)params->texture->height / wall_height;
	params->ip_x = get_impact_point(params->texture, mlx);
	if (mlx->ray->flag == 0)
	{
		if (mlx->ray->ray_angle > PI / 2 && mlx->ray->ray_angle < 3 * PI / 2)
			params->ip_x = params->texture->width - params->ip_x - 1;
	}
	else if (mlx->ray->flag == 1)
	{
		if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < PI)
			params->ip_x = params->texture->width - params->ip_x - 1;
	}
	params->ip_y = (u_pix - WH / 2 + wall_height / 2) * params->scale;
	if (params->ip_y < 0)
		params->ip_y = 0;
	if (params->ip_x < 0)
		params->ip_x = 0;
}

void	draw_wall_pixels(t_mlx *mlx, int d_pix, int u_pix, t_param *params)
{
	uint32_t	*pix;

	pix = (uint32_t *)params->texture->pixels;
	while (u_pix < d_pix)
	{
		ft_put_pixel(mlx, mlx->ray->index, u_pix,
			reverse_bytes(pix[(int)params->ip_y * params->texture->width + \
			(int)params->ip_x]));
		params->ip_y += params->scale;
		u_pix++;
	}
}
