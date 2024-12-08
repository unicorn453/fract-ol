/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:04:38 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/08 16:11:51 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	burning_ship(t_data *fractal)
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
		fractal->z.imaginary = 2 * fabs(real) * fabs(imaginary)
			+ fractal->c.imaginary;
		if (magnitude(fractal->z.real, fractal->z.imaginary) > 4.0)
			break ;
	}
	return (i);
}

int	clamp(int value, int min, int max)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
}

int	color_gradient_palette(int iteration, int max_iterations, t_data *fractal)
{
	double	t;
	int		base_color;
	int		r;
	int		g;
	int		b;

	t = (double)iteration / max_iterations;
	base_color = pre_defined_colors(fractal->num_color);
	r = ((base_color & 0xFF0000) >> 16) + (int)(9 * (1 - t) * t * t * t * 255);
	g = ((base_color & 0x00FF00) >> 8) + (int)(15 * (1 - t) * (1 - t) * t * t
			* 255);
	b = (base_color & 0x0000FF) + (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t
			* 255);
	r = clamp(r, 0, 255);
	g = clamp(g, 0, 255);
	b = clamp(b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}

void	draw_pixel(t_data *fractal, int x, int y)
{
	int	n;
	int	color;

	n = burning_ship(fractal);
	if (n == fractal->max_iterations)
		color = 0x000000;
	else
		color = color_gradient_palette(n, fractal->max_iterations, fractal);
	put_pixel(fractal, x, y, color);
}

void	create_burningship(t_data *fractal)
{
	int	x;
	int	y;

	x = 0;
	while (x < fractal->width)
	{
		y = 0;
		while (y < fractal->height)
		{
			set_complex_coordinates(fractal, x, y);
			draw_pixel(fractal, x, y);
			y++;
		}
		x++;
	}
}
