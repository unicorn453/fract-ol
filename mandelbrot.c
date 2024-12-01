/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:16:07 by kruseva           #+#    #+#             */
/*   Updated: 2024/11/30 13:27:11 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h" 


double magnitude(double real, double imaginary)
{
    return real * real + imaginary * imaginary;
}

int mandelbrot(complexNum c)
{

    complexNum z;
    z.real = 0;
    z.imaginary = 0;
    int i = 0;
    while(i < 600)
    {
        double real = z.real;
        double imaginary = z.imaginary;
        z.real = real * real - imaginary * imaginary + c.real;
        z.imaginary = 2 * real * imaginary + c.imaginary;
        if (magnitude(z.real, z.imaginary) > 2.0)
            break;
        i++;
    }
    return i;
}

void createMandelbrot(t_data *data)
{
    printf("Creating Mandelbrot set\n");
    printf("Width: %d, Height: %d\n", data->width, data->height);

    int width = data->width;
    int height = data->height;
    double x = -2.0;
    double y = -2.0;
    double dx = 4.0 / width;
    double dy = 4.0 / height;
    int i = 0;
    while (i < height)
    {
        int j = 0;
        while (j < width)
        {
            complexNum c;
            c.real = x + j * dx;
            c.imaginary = y + i * dy;
            int n = mandelbrot(c);
            int color = preDefinedColors(data->numColor);
            if (n == data->maxIterations)
                mlx_pixel_put(data->mlx, data->win, j, i, 0x000000);
            else
                mlx_pixel_put(data->mlx, data->win, j, i, color);
            j++;
        }
        i++;
    }
    printf("Finished creating Mandelbrot set\n");
}

int main(int argc, char **argv)
{
    printf("Program started\n");
    if (argc != 2)
    {
        printf("Usage: ./mandelbrot [mandelbrot]\n");
        return 1;
    }
    printf("Argument: %s\n", argv[1]);
    if (drawSet(&argv[1]) != 0)
    {
        printf("Error: drawSet failed\n");
        return 1;
    }
    return 0;
}