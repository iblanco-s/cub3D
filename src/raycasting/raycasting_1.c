#include "../../cub3D.h"

void debug_data(t_data data)
{
    printf("fd: %d\n", data.fd);
    printf("line: %s\n", data.line ? data.line : "NULL");
    printf("texture: %s\n", data.texture ? data.texture : "NULL");

    if (data.split_texture)
    {
        printf("split_texture:\n");
        for (int i = 0; data.split_texture[i] != NULL; i++)
        {
            printf("  [%d]: %s\n", i, data.split_texture[i]);
        }
    }
    else
    {
        printf("split_texture: NULL\n");
    }

    printf("map: %s\n", data.map ? data.map : "NULL");

    if (data.split_map)
    {
        printf("split_map:\n");
        for (int i = 0; data.split_map[i] != NULL; i++)
        {
            printf("  [%d]: %s\n", i, data.split_map[i]);
        }
    }
    else
    {
        printf("split_map: NULL\n");
    }

    if (data.map_copy)
    {
        printf("map_copy:\n");
        for (int i = 0; data.map_copy[i] != NULL; i++)
        {
            printf("  [%d]: %s\n", i, data.map_copy[i]);
        }
    }
    else
    {
        printf("map_copy: NULL\n");
    }

    printf("map_height: %d\n", data.map_height);
    printf("map_width: %d\n", data.map_width);
    printf("player_x: %d\n", data.player_x);
    printf("player_y: %d\n", data.player_y);
    printf("map_column: %d\n", data.map_column);
    printf("map_lines: %d\n", data.map_lines);
}

int raycasting(t_mlx *mlx, t_data data)
{
	debug_data(data);

    int color = 0x00FF00; 

    mlx->mlx_ptr = mlx_init();
    mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SW, SH, "Ventana MLX");

    mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, TILE_SIZE, TILE_SIZE, color); 

    mlx_loop(mlx->mlx_ptr);

    return 0;
}
