/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:13:21 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/08 16:09:50 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_in(t_data *data)
{
	double	zoom_factor;
	double	center_x;
	double	center_y;

	data->zoom *= 1.1;
	zoom_factor = 1.0 / data->zoom;
	center_x = data->complex_x;
	center_y = data->complex_y;
	data->complex_x = center_x + (data->c.real - center_x) * zoom_factor;
	data->complex_y = center_y + (data->c.imaginary - center_y) * zoom_factor;
	if (data->zoom > 100)
		data->max_iterations = 100;
	if (data->zoom > 1000)
		data->max_iterations = 200;
}

void	zoom_out(t_data *data)
{
	double	zoom_factor;
	double	center_x;
	double	center_y;

	if (data->zoom <= 1.0)
		return ;
	data->zoom /= 1.1;
	zoom_factor = 1.0 / data->zoom;
	center_x = data->complex_x;
	center_y = data->complex_y;
	data->complex_x = center_x - (data->c.real - center_x) * zoom_factor;
	data->complex_y = center_y - (data->c.imaginary - center_y) * zoom_factor;
	if (data->zoom <= 10)
		data->max_iterations = 50;
}

int	handle_mouse(int button, int x, int y, t_data *data)
{
	if (!data || x < 0 || x >= data->width || y < 0 || y >= data->height)
		return (0);
	if (ft_strcmp(data->name, "mandelbrot") == 0 || ft_strcmp(data->name,
			"burning_ship") == 0)
	{
		data->c.real = (x - data->width / 2.0) * 4.0 / (data->width
				* data->zoom) + data->complex_x;
		data->c.imaginary = (y - data->height / 2.0) * 4.0 / (data->height
				* data->zoom) + data->complex_y;
	}
	else if (ft_strcmp(data->name, "julia") == 0)
	{
		data->complex_x = (x - data->width / 2.0) * 4.0 / (data->width
				* data->zoom) + data->complex_x;
		data->complex_y = (y - data->height / 2.0) * 4.0 / (data->height
				* data->zoom) + data->complex_y;
	}
	if (button == 4)
		zoom_in(data);
	else if (button == 5)
		zoom_out(data);
	draw_set(data);
	return (1);
}

void	handle_keypress(int keycode, t_data *fractal)
{
	double	pan_factor;

	pan_factor = 0.1;
	if (keycode == KEY_UP)
		fractal->complex_y -= pan_factor / fractal->zoom;
	else if (keycode == KEY_DOWN)
		fractal->complex_y += pan_factor / fractal->zoom;
	else if (keycode == KEY_LEFT)
		fractal->complex_x -= pan_factor / fractal->zoom;
	else if (keycode == KEY_RIGHT)
		fractal->complex_x += pan_factor / fractal->zoom;
	else if (keycode == KEY_R)
	{
		fractal->zoom = 1;
		fractal->complex_x = 0;
		fractal->complex_y = 0;
	}
	else
	{
		if (keycode >= KEY_1 && keycode <= KEY_7)
			fractal->num_color = keycode - KEY_1 + 1;
	}
}

int	handle_key(int key, t_data *fractol)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(fractol->mlx, fractol->win);
		free(fractol);
		exit(0);
	}
	handle_keypress(key, fractol);
	draw_set(fractol);
	return (0);
}
