/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:07:08 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/01 16:51:54 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <stdio.h>
#include </Users/kruseva/Desktop/AllProjects/fractol/minilibx_opengl_20191021/mlx.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

typedef struct s_data {
    void *mlx;
    void *win;
    int x;
    int y;
    int width;
    int height;
    int numColor;
    int maxIterations;
} t_data;

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct complexNum
{
    double real;
    double imaginary;
} complexNum;

int keyInput(int key, t_data *data);
int preDefinedColors(int numColor);
int get_color_by_name(char *name);
int handle_key(int key, t_data *data);
int handle_mouse(int button, int x, int y, t_data *data);
void createMandelbrot(t_data *data);
int mandelbrot(complexNum c);
double magnitude(double real, double imaginary);
int drawSet(char **set);

#endif