/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:16:07 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/08 16:09:16 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	magnitude(double real, double imaginary)
{
	return (real * real + imaginary * imaginary);
}

int	mandelbrot(t_data *fractal)
{
	int		i;
	double	real;
	double	imaginary;

	fractal->z.real = 0;
	fractal->z.imaginary = 0;
	i = 0;
	while (++i < fractal->max_iterations)
	{
		real = fractal->z.real;
		imaginary = fractal->z.imaginary;
		fractal->z.real = real * real - imaginary * imaginary + fractal->c.real;
		fractal->z.imaginary = 2 * real * imaginary + fractal->c.imaginary;
		if (magnitude(fractal->z.real, fractal->z.imaginary) > 4.0)
			break ;
	}
	return (i);
}

int	get_color(t_data *fractal, int n)
{
	if (n == fractal->max_iterations)
		return (0x000000);
	else
		return (color_gradient_palette(n, fractal->max_iterations, fractal));
}

void	create_mandelbrot(t_data *fractal)
{
	int	x;
	int	y;
	int	n;
	int	color;

	x = 0;
	while (x < fractal->width)
	{
		y = 0;
		while (y < fractal->height)
		{
			set_complex_coordinates(fractal, x, y);
			n = mandelbrot(fractal);
			color = get_color(fractal, n);
			put_pixel(fractal, x, y, color);
			y++;
		}
		x++;
	}
}

void	set_complex_coordinates(t_data *fractal, int x, int y)
{
	fractal->c.real = (x - fractal->width / 2.0) * 4.0 / (fractal->width
			* fractal->zoom) + fractal->complex_x;
	fractal->c.imaginary = (y - fractal->height / 2.0) * 4.0 / (fractal->height
			* fractal->zoom) + fractal->complex_y;
}
