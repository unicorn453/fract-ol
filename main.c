/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:08:45 by kruseva           #+#    #+#             */
/*   Updated: 2024/11/29 15:17:25 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include </Users/kruseva/Desktop/AllProjects/fractol/minilibx_opengl_20191021/mlx.h>
// #include <stdlib.h>
// #include <stdio.h> // For printf
// #include <string.h> // For strcmp

// #define WIN_WIDTH 800
// #define WIN_HEIGHT 600

// // Structure for color names and their corresponding values
// struct s_col_name {
//     char *name;
//     int color;
// };

// // Include the color names array
// extern struct s_col_name mlx_col_name[];


// int get_color_by_name(char *name)
// {
//     for (int i = 0; mlx_col_name[i].name != 0; i++)
//     {
//         if (strcmp(mlx_col_name[i].name, name) == 0)
//             return mlx_col_name[i].color;
//     }
//     return -1;
// }

// int main(int argc, char **argv)
// {
//     if (argc != 3) // Check if user provided start and end colors
//     {
//         printf("Usage: %s <start_color> <end_color>\n", argv[0]);
//         printf("Example: %s \"red\" \"blue\"\n", argv[0]);
//         return (1);
//     }

//     int start_color = get_color_by_name(argv[1]);
//     int end_color = get_color_by_name(argv[2]);

//     if (start_color == -1 || end_color == -1)
//     {
//         printf("Invalid color name provided.\n");
//         return (1);
//     }

//     void *mlx = mlx_init();
//     void *win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Gradient");
//     void *img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);

//     int *pixels;
//     int bpp, size_line, endian;

//     pixels = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);


//     for (int y = 0; y < WIN_HEIGHT; y++)
//     {
//         for (int x = 0; x < WIN_WIDTH; x++)
//         {
//             float ratio = (float)x / WIN_WIDTH;
//             int r = ((start_color >> 16) & 0xFF) * (1 - ratio) + ((end_color >> 16) & 0xFF) * ratio;
//             int g = ((start_color >> 8) & 0xFF) * (1 - ratio) + ((end_color >> 8) & 0xFF) * ratio;
//             int b = (start_color & 0xFF) * (1 - ratio) + (end_color & 0xFF) * ratio;

//             int color = (r << 16) | (g << 8) | b;
//             pixels[y * (size_line / 4) + x] = color;
//         }
//     }

//     mlx_put_image_to_window(mlx, win, img, 0, 0);
//     mlx_loop(mlx);
//     return (0);
// }