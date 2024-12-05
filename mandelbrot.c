/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:16:07 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/05 22:14:53 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double magnitude(double real, double imaginary)
{
    return real * real + imaginary * imaginary;
}


int mandelbrot(t_data *fractal)
{
    fractal->z.real = 0;
    fractal->z.imaginary = 0;
    int i = 0;
    while (++i < fractal->maxIterations)
    {
        double real = fractal->z.real;
        double imaginary = fractal->z.imaginary;
        fractal->z.real = real * real - imaginary * imaginary + fractal->c.real;
        fractal->z.imaginary = 2 * real * imaginary + fractal->c.imaginary;
        if (magnitude(fractal->z.real, fractal->z.imaginary) > 2.0)
            break;
    }
    return i;
}



void createMandelbrot(t_data *fractal)
{
    int color;
    for (int x = 0; x < fractal->width; x++)
    {
        for (int y = 0; y < fractal->height; y++)
        {
            fractal->c.real = (x - fractal->width / 2.0) * 4.0 / (fractal->width * fractal->zoom) + fractal->complex_x;
            fractal->c.imaginary = (y - fractal->height / 2.0) * 4.0 / (fractal->height * fractal->zoom) + fractal->complex_y;

            int n = mandelbrot(fractal);

            color = (n == fractal->maxIterations) ? 0x000000 : preDefinedColors(fractal->numColor) + (n * 255 / fractal->maxIterations);
            put_pixel(fractal, x, y, color);
        }
    }
}



int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: ./fractol [mandelbrot]\n");
        printf("Usage: ./fractol [julia] real_num imaginary_num\n");
        printf("List fractals: julia, mandelbrot\n");
        return 1;
    }
    printf("Argument: %s\n", argv[1]);

    if(strcmp(argv[1], "mandelbrot") == 0 || strcmp(argv[1], "burning_ship") == 0)
    {
        if(initialize(&argv[1]) != 0)
        {
            printf("Error: initialize failed\n");
            return 1;
        }
    }
    else if(strcmp(argv[1], "julia") == 0)
    {
        if(argv[2] == NULL || argv[3] == NULL)
        {
            printf("Usage: ./fractol [julia] real_num imaginary_num\n");
            return 1;
        }
        if(initialize_julia(&argv[1], &argv[2], &argv[3]) != 0)
        {
            printf("Error: initialize_julia failed\n");
            return 1;
        }
    }
    return 0;
}


