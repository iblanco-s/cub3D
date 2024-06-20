#include "../../cub3D.h"

int main()
{
    void *mlx_ptr;
    void *win_ptr;
    int x = 400;
    int y = 300;
    int color = 0x00FF00; // Color verde en formato RGB

    mlx_ptr = mlx_init(); // Inicializa la biblioteca
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Ventana MLX"); // Crea una nueva ventana

    mlx_pixel_put(mlx_ptr, win_ptr, x, y, color); // Dibuja un pixel en la posición (x, y) con el color especificado

    mlx_loop(mlx_ptr); // Inicia el loop de eventos

    return 0;
}