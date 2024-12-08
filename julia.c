/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:35:10 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/08 16:11:23 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(t_data *fractal)
{
	int		i;
	double	real;
	double	imaginary;
	double	temp_real;

	i = 0;
	real = fractal->z.real;
	imaginary = fractal->z.imaginary;
	while (++i < fractal->max_iterations)
	{
		temp_real = real * real - imaginary * imaginary + fractal->c.real;
		imaginary = 2 * real * imaginary + fractal->c.imaginary;
		real = temp_real;
		fractal->z.real = real;
		fractal->z.imaginary = imaginary;
		if (magnitude(real, imaginary) > 4.0)
			break ;
	}
	return (i);
}

void	set_complex_values(t_data *fractal, int x, int y)
{
	fractal->z.real = (x - fractal->width / 2.0) * 4.0 / (fractal->width
			* fractal->zoom) + fractal->complex_x;
	fractal->z.imaginary = (y - fractal->height / 2.0) * 4.0 / (fractal->height
			* fractal->zoom) + fractal->complex_y;
}

int	calculate_color(t_data *fractal, int n)
{
	if (n == fractal->max_iterations)
		return (0x000000);
	else
		return (color_gradient_palette(n, fractal->max_iterations, fractal));
}

void	create_julia(t_data *fractal)
{
	int	color;
	int	x;
	int	y;
	int	n;

	x = 0;
	while (x < fractal->width)
	{
		y = 0;
		while (y < fractal->height)
		{
			set_complex_values(fractal, x, y);
			n = julia(fractal);
			color = calculate_color(fractal, n);
			put_pixel(fractal, x, y, color);
			y++;
		}
		x++;
	}
}

int	initialize_julia(char **name, char **real, char **imaginary)
{
	t_data	*fractal;

	fractal = initialize_fractal(name);
	fractal->c.real = ft_atof(*real);
	fractal->c.imaginary = ft_atof(*imaginary);
	if (fractal->c.real < -2.0 || fractal->c.real > 2.0
		|| fractal->c.imaginary < -2.0 || fractal->c.imaginary > 2.0)
	{
		ft_printf("Error: values must be between -2.0 and 2.0.\n");
		free(fractal);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(*name, "julia") == 0)
		draw_set(fractal);
	else
	{
		ft_printf("Error: Unsupported fractal type '%s'\n", *name);
		free(fractal);
		exit(EXIT_FAILURE);
	}
	setup_hooks_and_loop(fractal);
	return (0);
}
