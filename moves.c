/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:13:21 by kruseva           #+#    #+#             */
/*   Updated: 2024/11/30 14:00:53 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"

void moveUp(int *y, int *height)
{
    *y -= *height / 10;
}

void moveDown(int *y, int *height)
{
    *y += *height / 10;
}

void moveLeft(int *x, int *width)
{
    *x -= *width / 10;
}

void moveRight(int *x, int *width)
{
    *x += *width / 10;
}
void zoomIn(int *x, int *y, int *width, int *height)
{
    *x += *width / 10;
    *y += *height / 10;
    *width -= *width / 5;
    *height -= *height / 5;
}

void zoomOut(int *x, int *y, int *width, int *height)
{
    *x -= *width / 10;
    *y -= *height / 10;
    *width += *width / 5;
    *height += *height / 5;
}


void reset(int *x, int *y, int *width, int *height)
{
    *x = 0;
    *y = 0;
    *width = WIN_WIDTH;
    *height = WIN_HEIGHT;
}

int keyInput(int key, t_data *data)
{
    if (key == 126)
        moveUp(&data->y, &data->height);
    else if (key == 125)
        moveDown(&data->y, &data->height);
    else if (key == 123)
        moveLeft(&data->x, &data->width);
    else if (key == 124)
        moveRight(&data->x, &data->width);
    else if (key == 69)
    {
        zoomIn(&data->x, &data->y, &data->width, &data->height);
        data->maxIterations += 50;
    }
    else if (key == 78)
    {
        zoomOut(&data->x, &data->y, &data->width, &data->height);
        if (data->maxIterations > 50)
            data->maxIterations -= 50;
    }
    else if (key == 15) 
        reset(&data->x, &data->y, &data->width, &data->height);
    else
        return (0);

    createMandelbrot(data);
    return (1);
}



int handle_key(int key, t_data *data)
{
    if (key == 126)
        moveUp(&data->y, &data->height);
    else if (key == 125)
        moveDown(&data->y, &data->height);
    else if (key == 123) // Left arrow
        moveLeft(&data->x, &data->width);
    else if (key == 124) // Right arrow
        moveRight(&data->x, &data->width);
    else if (key == 69)
        data->maxIterations += 50;
    else if (key == 78) 
    {
        if (data->maxIterations > 50)
            data->maxIterations -= 50;
    }
    else
        return (0);

  
    mlx_clear_window(data->mlx, data->win);
    createMandelbrot(data);
    return (1);
}


int handle_mouse(int button, int x, int y, t_data *data)
{
    (void)x; 
    (void)y;
    if (button == 4)
        zoomIn(&data->x, &data->y, &data->width, &data->height);
    else if (button == 5) 
        zoomOut(&data->x, &data->y, &data->width, &data->height);
    else
        return (0);

    
    mlx_clear_window(data->mlx, data->win);
    createMandelbrot(data);
    return (1);
}
