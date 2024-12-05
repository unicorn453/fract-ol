/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:35:10 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/05 18:01:22 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int julia(t_data *fractal)
{
    int i = 0;
    double real = fractal->z.real;
    double imaginary = fractal->z.imaginary;

    while (++i < fractal->maxIterations)
    {
        double temp_real = real * real - imaginary * imaginary + fractal->c.real;
        imaginary = 2 * real * imaginary + fractal->c.imaginary;
        real = temp_real;

        fractal->z.real = real;
        fractal->z.imaginary = imaginary;

        if (magnitude(real, imaginary) > 2.0) 
            break;
    }
    return i;
}

void createJulia(t_data *fractal)
{
    int color;
    for (int x = 0; x < fractal->width; x++)
    {
        for (int y = 0; y < fractal->height; y++)
        {
            fractal->z.real = (x - fractal->width / 2.0) * 4.0 / (fractal->width * fractal->zoom) + fractal->complex_x;
            fractal->z.imaginary = (y - fractal->height / 2.0) * 4.0 / (fractal->height * fractal->zoom) + fractal->complex_y;

            int n = julia(fractal);

            color = (n == fractal->maxIterations) ? 0x000000 : preDefinedColors(fractal->numColor) + (n * 255 / fractal->maxIterations);
            put_pixel(fractal, x, y, color);
        }
    }
}
