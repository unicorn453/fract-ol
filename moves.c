/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:13:21 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/05 14:30:35 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"

// int input_key(int key, t_data *data)
// {
//     if (key == KEY_ESC)
//         exit(0);
//     if (key == KEY_PLUS)
//     {
//         data->maxIterations += 10;
//         drawSet(data);
//     }
//     if (key == KEY_MINUS)
//     {
//         data->maxIterations -= 10;
//         drawSet(data);
//     }
//     if (key == KEY_R)
//     {
//         data->x = 0;
//         data->y = 0;
//         data->width = WIN_WIDTH;
//         data->height = WIN_HEIGHT;
//         data->maxIterations = 50;
//         data->numColor = 0;
//         drawSet(data);
//     }
//     if (key == KEY_UP)
//     {
//         data->y -= 50;
//         drawSet(data);
//     }
//     if (key == KEY_DOWN)
//     {
//         data->y += 50;
//         drawSet(data);
//     }
//     if (key == KEY_LEFT)
//     {
//         data->x -= 50;
//         drawSet(data);
//     }
//     if (key == KEY_RIGHT)
//     {
//         data->x += 50;
//         drawSet(data);
//     }
//     return (0);
// }

void zoomIn(t_data *data)
{
    data->zoom *= 1.1;

    double zoomFactor = 1.0 / data->zoom;
    double centerX = data->complex_x;
    double centerY = data->complex_y;

    data->complex_x = centerX + (data->c.real - centerX) * zoomFactor;
    data->complex_y = centerY + (data->c.imaginary - centerY) * zoomFactor;

    if (data->zoom > 100)
        data->maxIterations = 100;
    if (data->zoom > 1000)
        data->maxIterations = 200;
}

void zoomOut(t_data *data)
{
    if (data->zoom <= 1.0)
        return;


    data->zoom /= 1.1;


    double zoomFactor = 1.0 / data->zoom;
    double centerX = data->complex_x;
    double centerY = data->complex_y;

    data->complex_x = centerX - (data->c.real - centerX) * zoomFactor;
    data->complex_y = centerY - (data->c.imaginary - centerY) * zoomFactor;


    if (data->zoom <= 10)
        data->maxIterations = 50;
}

int handle_mouse(int button, int x, int y, t_data *data)
{

    if (!data || x < 0 || x >= data->width || y < 0 || y >= data->height)
        return (0);

 
    data->c.real = (x - data->width / 2.0) * 4.0 / (data->width * data->zoom) + data->complex_x;
    data->c.imaginary = (y - data->height / 2.0) * 4.0 / (data->height * data->zoom) + data->complex_y;

    if (button == 4) 
        zoomIn(data);
    else if (button == 5)
        zoomOut(data);
    else
        return (0);

    drawSet(data);
    return (1);
}

void handle_keypress(int keycode, t_data *fractal) {
    double pan_factor = 0.1;
    if (keycode == KEY_UP) { 
        fractal->complex_y -= pan_factor / fractal->zoom;
    } else if (keycode == KEY_DOWN) { 
        fractal->complex_y += pan_factor / fractal->zoom;
    } else if (keycode == KEY_LEFT) { 
        fractal->complex_x -= pan_factor / fractal->zoom;
    } else if (keycode == KEY_RIGHT) { 
        fractal->complex_x += pan_factor / fractal->zoom;
    }
}

int handle_key(int key, t_data *fractol)
{
    if (key == KEY_ESC)
        exit(0);
        handle_keypress(key, fractol);
        drawSet(fractol);
    return (0);
}