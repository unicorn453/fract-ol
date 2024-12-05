/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:13:21 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/05 22:23:36 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoomIn(t_data *data)
{
	double	zoomFactor;
	double	centerX;
	double	centerY;

	data->zoom *= 1.1;
	zoomFactor = 1.0 / data->zoom;
	centerX = data->complex_x;
	centerY = data->complex_y;
	data->complex_x = centerX + (data->c.real - centerX) * zoomFactor;
	data->complex_y = centerY + (data->c.imaginary - centerY) * zoomFactor;
	if (data->zoom > 100)
		data->maxIterations = 100;
	if (data->zoom > 1000)
		data->maxIterations = 200;
}

void	zoomOut(t_data *data)
{
	double	zoomFactor;
	double	centerX;
	double	centerY;

	if (data->zoom <= 1.0)
		return ;
	data->zoom /= 1.1;
	zoomFactor = 1.0 / data->zoom;
	centerX = data->complex_x;
	centerY = data->complex_y;
	data->complex_x = centerX - (data->c.real - centerX) * zoomFactor;
	data->complex_y = centerY - (data->c.imaginary - centerY) * zoomFactor;
	if (data->zoom <= 10)
		data->maxIterations = 50;
}

int	handle_mouse(int button, int x, int y, t_data *data)
{
	if (!data || x < 0 || x >= data->width || y < 0 || y >= data->height)
		return (0);
	if (strcmp(data->name, "mandelbrot") == 0 || strcmp(data->name, "burning_ship") == 0)
	{
		data->c.real = (x - data->width / 2.0) * 4.0 / (data->width
				* data->zoom) + data->complex_x;
		data->c.imaginary = (y - data->height / 2.0) * 4.0 / (data->height
				* data->zoom) + data->complex_y;
	} else if (strcmp(data->name, "julia") == 0)
	{
		data->complex_x = (x - data->width / 2.0) * 4.0 / (data->width * data->zoom) + data->complex_x;
	data->complex_y = (y - data->height / 2.0) * 4.0 / (data->height * data->zoom) + data->complex_y;

	}
	if (button == 4)
		zoomIn(data);
	else if (button == 5)
		zoomOut(data);
	else
		return (0);
	drawSet(data);
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
	else if (keycode == KEY_1)
		fractal->numColor = 1;
	else if (keycode == KEY_2)
		fractal->numColor = 2;
	else if (keycode == KEY_3)
		fractal->numColor = 3;
	else if (keycode == KEY_4)
		fractal->numColor = 4;
	else if (keycode == KEY_5)
		fractal->numColor = 5;
	else if (keycode == KEY_6)
		fractal->numColor = 6;
	else if (keycode == KEY_7)
		fractal->numColor = 7;
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
	drawSet(fractol);
	return (0);
}