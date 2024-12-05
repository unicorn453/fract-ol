/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:04:38 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/05 22:23:48 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int burning_ship(t_data *fractal)
{
    fractal->z.real = 0;
    fractal->z.imaginary = 0;
    int i = 0;
    while (++i < fractal->maxIterations)
    {
        double real = fractal->z.real;
        double imaginary = fractal->z.imaginary;


        fractal->z.real = real * real - imaginary * imaginary + fractal->c.real;
        fractal->z.imaginary = 2 * fabs(real) * fabs(imaginary) + fractal->c.imaginary;

    
        if (magnitude(fractal->z.real, fractal->z.imaginary) > 4.0)
            break;
    }
    return i;
}

int colorGradientPalette(int iteration, int maxIterations, t_data *fractal) {
    double t = (double)iteration / maxIterations;


    int baseColor = preDefinedColors(fractal->numColor);
    int baseRed = (baseColor & 0xFF0000) >> 16;
    int baseGreen = (baseColor & 0x00FF00) >> 8;
    int baseBlue = baseColor & 0x0000FF;

    int r = baseRed + (int)(9 * (1 - t) * t * t * t * 255); 
    int g = baseGreen + (int)(15 * (1 - t) * (1 - t) * t * t * 255); 
    int b = baseBlue + (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

    r = (r > 255) ? 255 : (r < 0) ? 0 : r;
    g = (g > 255) ? 255 : (g < 0) ? 0 : g;
    b = (b > 255) ? 255 : (b < 0) ? 0 : b;

    return (r << 16) | (g << 8) | b;
}


void createBurningship(t_data *fractal)
{
    int color;
    for (int x = 0; x < fractal->width; x++)
    {
        for(int y = 0; y < fractal->height; y++)
        {
            fractal->c.real = (x - fractal->width / 2.0) * 4.0 / (fractal->width * fractal->zoom) + fractal->complex_x;
            fractal->c.imaginary = (y - fractal->height / 2.0) * 4.0 / (fractal->height * fractal->zoom) + fractal->complex_y;

            int n = burning_ship(fractal);

            color = (n == fractal->maxIterations) ? 0x000000 : colorGradientPalette(n, fractal->maxIterations, fractal);
            put_pixel(fractal, x, y, color);
        }
    }
}


