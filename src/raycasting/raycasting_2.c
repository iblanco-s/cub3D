/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:45:51 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/16 10:46:47 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	get_rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	ft_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0 || x >= WW || y < 0 || y >= WH)
		return ;
	mlx_put_pixel(mlx->img, x, y, color);
}

void	draw_floor_ceiling(t_mlx *mlx, int ray, int d_pix, int u_pix)
{
	int	i;
	int	color;

	i = d_pix;
	color = get_rgba(ft_atoi(mlx->dat->floor[0]),
			ft_atoi(mlx->dat->floor[1]), ft_atoi(mlx->dat->floor[2]), 255);
	while (i < WH)
		ft_put_pixel(mlx, ray, i++, color);
	color = get_rgba(ft_atoi(mlx->dat->ceiling[0]),
			ft_atoi(mlx->dat->ceiling[1]), ft_atoi(mlx->dat->ceiling[2]), 255);
	i = 0;
	while (i < u_pix)
		ft_put_pixel(mlx, ray, i++, color);
}

void	draw_wall(t_mlx *mlx, int d_pix, int u_pix, double wall_height)
{
	t_param	params;

	wall_params(mlx, u_pix, wall_height, &params);
	draw_wall_pixels(mlx, d_pix, u_pix, &params);
}

void	draw_wall_segment(t_mlx *mlx, int ray)
{
	double	wall_height;
	double	d_pix;
	double	u_pix;

	mlx->ray->distance *= cos(
			normalize_angle(mlx->ray->ray_angle - mlx->play->playr_dir));
	wall_height = (TILE_SIZE / mlx->ray->distance) * (WW / 2) / \
		tan(mlx->play->fov_rad / 2);
	d_pix = (WH / 2) + (wall_height / 2);
	u_pix = (WH / 2) - (wall_height / 2);
	if (d_pix > WH)
		d_pix = WH;
	if (u_pix < 0)
		u_pix = 0;
	mlx->ray->index = ray;
	draw_wall(mlx, d_pix, u_pix, wall_height);
	draw_floor_ceiling(mlx, ray, d_pix, u_pix);
}
