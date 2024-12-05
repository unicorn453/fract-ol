/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawSet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:06:08 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/05 22:17:43 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fractol.h"

void usual_initializations(t_data *fractal, char **name)
{
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
}

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
        return get_color_by_name("pink");
    if (numColor == 6)
        return get_color_by_name("magenta");
    if (numColor == 7)
        return get_color_by_name("purple");

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
    if (strcmp(fractal->name, "mandelbrot") == 0)
        createMandelbrot(fractal);
    else if (strcmp(fractal->name, "julia") == 0)
        createJulia(fractal);
    else if (strcmp(fractal->name, "burning_ship") == 0)
        createBurningship(fractal);
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
    if (!fractal)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    fractal->name = *name;
    usual_initializations(fractal, name);

    if (strcmp(*name, "mandelbrot") == 0 || strcmp(*name, "burning_ship") == 0)
    {
        drawSet(fractal);
    }
    else {
        fprintf(stderr, "Error: Unsupported fractal type '%s'.\n", *name);
        free(fractal);
        exit(EXIT_FAILURE);
    }

    mlx_hook(fractal->win, 2, 1L << 0, handle_key, fractal);
    mlx_hook(fractal->win, 4, 1L << 2, handle_mouse, fractal);
    mlx_hook(fractal->win, 17, 0, close_window, fractal);
    mlx_loop(fractal->mlx);

    return (NULL);
}
int initialize_julia(char **name, char **real, char **imaginary)
{
    if (!real || !imaginary || !*real || !*imaginary)
    {
        printf("Usage: ./fractol [julia] real_num imaginary_num\n");
        exit(EXIT_FAILURE);
    }

    t_data *fractal = (t_data *)malloc(sizeof(t_data));
    if (!fractal)
    {
        printf("Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    fractal->name = *name;
    usual_initializations(fractal, name);
    fractal->c.real = atof(*real);
    fractal->c.imaginary = atof(*imaginary);

    if (strcmp(*name, "julia") == 0)
    {
        drawSet(fractal);
    }
    else
    {
        printf("Error: Unsupported fractal type '%s'\n", *name);
        free(fractal);
        exit(EXIT_FAILURE);
    }

    mlx_hook(fractal->win, 2, 1L << 0, handle_key, fractal);
    mlx_hook(fractal->win, 4, 1L << 2, handle_mouse, fractal);
    mlx_hook(fractal->win, 17, 0, close_window, fractal);
    mlx_loop(fractal->mlx);

    return 0;
}
