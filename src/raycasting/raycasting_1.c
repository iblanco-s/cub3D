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

int raycasting(t_data data)
{
	debug_data(data);

    void *mlx_ptr;
    void *win_ptr;
    int x = 400;
    int y = 300;
    int color = 0x00FF00; 

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Ventana MLX");

    mlx_pixel_put(mlx_ptr, win_ptr, x, y, color); 

    mlx_loop(mlx_ptr);

    return 0;
}