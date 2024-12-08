/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:06:08 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/08 16:10:33 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	pre_defined_colors(int numColor)
{
	if (numColor == 0)
		return (get_color_by_name("black"));
	if (numColor == 1)
		return (get_color_by_name("blue"));
	if (numColor == 2)
		return (get_color_by_name("green"));
	if (numColor == 3)
		return (get_color_by_name("red"));
	if (numColor == 4)
		return (get_color_by_name("yellow"));
	if (numColor == 5)
		return (get_color_by_name("pink"));
	if (numColor == 6)
		return (get_color_by_name("magenta"));
	if (numColor == 7)
		return (get_color_by_name("purple"));
	return (0);
}

void	draw_set(t_data *fractal)
{
	int	combined;

	fractal->width = WIN_WIDTH;
	fractal->height = WIN_HEIGHT;
	combined = WIN_WIDTH * WIN_HEIGHT;
	ft_memset(fractal->addr, 0, combined * (fractal->bits_per_pixel / 8));
	if (ft_strcmp(fractal->name, "mandelbrot") == 0)
		create_mandelbrot(fractal);
	else if (ft_strcmp(fractal->name, "julia") == 0)
		create_julia(fractal);
	else if (ft_strcmp(fractal->name, "burning_ship") == 0)
		create_burningship(fractal);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

void	put_pixel(t_data *fractal, int x, int y, int color)
{
	char	*dst;

	dst = fractal->addr + (y * fractal->line_length + x
			* (fractal->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_color_by_name(char *name)
{
	extern struct s_col_name	mlx_col_name[];
	int							i;

	i = 0;
	while (mlx_col_name[i].name != 0)
	{
		if (ft_strcmp(mlx_col_name[i].name, name) == 0)
			return (mlx_col_name[i].color);
		i++;
	}
	return (-1);
}

void	setup_hooks_and_loop(t_data *fractal)
{
	mlx_hook(fractal->win, 2, 1L << 0, handle_key, fractal);
	mlx_hook(fractal->win, 4, 1L << 2, handle_mouse, fractal);
	mlx_hook(fractal->win, 17, 0, close_window, fractal);
	mlx_loop(fractal->mlx);
}
