/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawSet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:06:08 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/01 21:26:26 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mandelbrot.h" 


int preDefinedColors(int numColor)
{
    if (numColor == 0)
        return get_color_by_name("black");
    if (numColor == 1)
        return get_color_by_name("blue");
    if (numColor == 2)
        return get_color_by_name("green");
    if (numColor == 3)
        return get_color_by_name("red");
    if (numColor == 4)
        return get_color_by_name("yellow");
    if (numColor == 5)
        return get_color_by_name("cyan");

    return 0;
}

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
    return (0);
}
void drawSet(t_data *fractal)
{
    fractal->width = WIN_WIDTH;
    fractal->height = WIN_HEIGHT;

    memset(fractal->addr, 0, WIN_WIDTH * WIN_HEIGHT * (fractal->bits_per_pixel / 8));
    createMandelbrot(fractal);
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

struct s_col_name {
    char *name;
    int color;
};

void put_pixel(t_data *fractal, int x, int y, int color)
{
    char *dst;
    dst = fractal->addr + (y * fractal->line_length + x * (fractal->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

extern struct s_col_name mlx_col_name[];

int get_color_by_name(char *name)
{
    for (int i = 0; mlx_col_name[i].name != 0; i++)
    {
        if (strcmp(mlx_col_name[i].name, name) == 0)
            return mlx_col_name[i].color;
    }
    return -1;
}



void *initialize(char **name)
{
    t_data *fractal;
    fractal = (t_data *)malloc(sizeof(t_data));
    fractal->mlx = mlx_init();
    fractal->win = mlx_new_window(fractal->mlx, WIN_WIDTH, WIN_HEIGHT, *name);
    fractal->img = mlx_new_image(fractal->mlx, WIN_WIDTH, WIN_HEIGHT);
    fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bits_per_pixel, &fractal->line_length, &fractal->endian);
    fractal->maxIterations = 50;
    fractal->numColor = 0;
    fractal->x = 0;
    fractal->y = 0;
    fractal->width = WIN_WIDTH;
    fractal->height = WIN_HEIGHT;
    fractal->zoom = 1;
    fractal->complex_x = 0;
    fractal->complex_y = 0;
    fractal->name = *name;

    if (strcmp(*name, "mandelbrot") == 0)
    {
        drawSet(fractal);
    }

    mlx_hook(fractal->win, 2, 1L << 0, handle_key, fractal);
    mlx_hook(fractal->win, 4, 1L << 2, handle_mouse, fractal);
    mlx_hook(fractal->win, 17, 0, close_window, fractal);
    mlx_loop(fractal->mlx);

    return (NULL);
}