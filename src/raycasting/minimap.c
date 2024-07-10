/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:25:50 by iblanco-          #+#    #+#             */
/*   Updated: 2024/07/10 13:40:06 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void convert_player_to_0(char **map_copy)
{
    for (int i = 0; map_copy[i]; i++)
    {
        for (int j = 0; map_copy[i][j]; j++)
        {
            if (map_copy[i][j] == 'N' || map_copy[i][j] == 'W' || 
                map_copy[i][j] == 'S' || map_copy[i][j] == 'E')
            {
                map_copy[i][j] = '0';
            }
        }
    }
}
void	draw_cell(t_mlx *mlx, int i, int j, int color)
{
	int x;
	int y;

	y = 0;
	if (color == 0x000000 || color == 0xFF69B4)
		return;
	while (y < 15)
	{
		x = 0;
		while (x < 15)
		{
			if (x == 0 || x == 14 || y == 0 || y == 14)
				x = x;//mlx_put_pixel(mlx->img, j * 15 + x, i * 15 + y, 0x000000); // Borde negro
			else
				mlx_put_pixel(mlx->img, j * 15 + x, i * 15 + y, color); // Interior de la celda
			x++;
		}
		y++;
	}
}

void	draw_player(t_mlx *mlx)
{
	int x;
	int y;

	y = 0;
	while (y < 7)
	{
		x = 0;
		while (x < 7)
		{
			mlx_put_pixel(mlx->img, ((mlx->play->playr_x * 15) / TILE_SIZE) + x,
				((mlx->play->playr_y * 15) / TILE_SIZE) + y, get_rgba(255, 0, 0, 255));
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_mlx *mlx)
{
	int i;
	int j;
	int color;

	i = 0;
	convert_player_to_0(mlx->dat->map_copy);
	while (i < mlx->dat->map_height)
	{
		j = 0;
		while (j < mlx->dat->map_width)
		{
			if (mlx->dat->map_copy[i][j] == '1')
				color = 0x000000; // Negro
			else if (mlx->dat->map_copy[i][j] == '0')
				color = 0xFFFFFF; // Blanco
			else //(mlx->dat->map_copy[i][j] == ' ')
				color = 0xFF69B4; // Rosa
			draw_cell(mlx, i, j, color);
			j++;
		}
		i++;
	}
	draw_player(mlx);
}
