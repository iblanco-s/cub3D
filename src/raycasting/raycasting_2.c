/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:45:51 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/03 11:41:54 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r * 0x1000000) + (g * 0x10000) + (b * 0x100) + a;
}

void	ft_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= WW)
		return ;
	if (y < 0)
		return ;
	else if (y >= WH)
		return ;
	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, color);
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
	double		ip_x;
	double		ip_y;
	t_mlxtex	*tex;
	uint32_t	*pix;
	double		scale;

	tex = get_texture(mlx, mlx->ray->flag);
	pix = (uint32_t *)tex->pixel;
	scale = (double)tex->height / wall_height;
	ip_x = get_impact_point(tex, mlx);
	ip_y = (u_pix - (WH / 2) + (wall_height / 2)) * scale;
	if (ip_y < 0)
		ip_y = 0;
	while (u_pix < d_pix)
	{
		ft_put_pixel(mlx, mlx->ray->index, u_pix,
			reverse_bytes(pix[(int)ip_y * tex->width + (int)ip_x]));
		ip_y += scale;
		u_pix++;
	}	
}

void	draw_wall_segment(t_mlx *mlx, int ray)
{
	double	wall_height;
	double	d_pix;
	double	u_pix;

	mlx->ray->distance *= cos(mlx->ray->ray_angle - mlx->play->playr_dir);
	wall_height = (TILE_SIZE / mlx->ray->distance) * (WW / 2) /
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