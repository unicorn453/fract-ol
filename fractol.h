/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:07:08 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/05 19:09:23 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

#include <stdio.h>
#include </Users/kruseva/Desktop/AllProjects/fractol/minilibx_opengl_20191021/mlx.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>


# define KEY_ESC 53
# define KEY_PLUS 43
# define KEY_MINUS 45
# define KEY_R 15
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define WIN_WIDTH 800
# define WIN_HEIGHT 800
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_6 22
# define KEY_7 26


typedef struct s_complex {
    double real;
    double imaginary;
} t_complex;


typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    
    int     width;
    int     height;
    
    double  zoom;
    double  complex_x;
    double  complex_y;
    
    int     x;
    int     y;
    
    int     maxIterations;
    int     numColor;
    
    char    *name;
    
    t_complex   c;
    t_complex   z;
} t_data;


void usual_initializations(t_data *fractal, char **name);
void *initialize(char **name);
int initialize_julia(char **name, char **real, char **imaginary);
// void *initialize_burning_ship(char **name);
int handle_key(int key, t_data *fractol);

int handle_mouse(int button, int x, int y, t_data *data);
void createMandelbrot(t_data *fractal);
void createJulia(t_data *fractal);
void createBurningship(t_data *fractal);
int mandelbrot(t_data *fractal);
double magnitude(double real, double imaginary);
void drawSet(t_data *fractal);
void zoomIn(t_data *data);
void zoomOut(t_data *data);
int close_window(t_data *data);
int preDefinedColors(int numColor);
void put_pixel(t_data *fractal, int x, int y, int color);


int get_color_by_name(char *name);
int getPredefinedColor(int numColor);

#endif
