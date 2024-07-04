/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:45:51 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/04 16:09:12 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	get_rgba(int r, int g, int b, int a)
{
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

void	ft_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int	index;

	if (x < 0 || x >= WW || y < 0 || y >= WH)
        return ;
    index = (y * mlx->size_line) + (x * (mlx->bpp / 8));
    *(unsigned int *)(mlx->img_data + index) = color;
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
	t_img		*img;
	double		scale;
	int			pixel_index;
	int			pixel_value;

	img = get_texture(mlx, mlx->ray->flag);
	scale = (double)img->height / wall_height;


    scale = (double)img->height / wall_height;
    ip_x = get_impact_point(img, mlx);

    // Ensure ip_x is within bounds
    if (ip_x < 0) ip_x = 0;
    if (ip_x >= img->width) ip_x = img->width - 1;
    int screen_y = u_pix;

	while (screen_y < d_pix && screen_y < WH)
	{
		
       	// Calculate texture y-coordinate
        ip_y = (int)((screen_y - u_pix) * scale);
        
        // Ensure ip_y is within bounds
        if (ip_y < 0) ip_y = 0;
        if (ip_y >= img->height) ip_y = img->height - 1;

		pixel_index = (ip_y * img->width + (int)ip_x) * (img->bpp / 8);
 		if (pixel_index >= 0 && pixel_index < (img->width * img->height * (img->bpp / 8)))
		{
			pixel_value = *(int *)(img->data + pixel_index);
			ft_put_pixel(mlx, mlx->ray->index, screen_y,
				reverse_bytes(pixel_value));
		}
		else
			printf("Error: pixel_index fuera de los límites\n");
		screen_y++;
	}
}

void	draw_wall_segment(t_mlx *mlx, int ray)
{
	double	wall_height;
	double	d_pix;
	double	u_pix;

	mlx->ray->distance *= cos(mlx->ray->ray_angle - mlx->play->playr_dir);
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
