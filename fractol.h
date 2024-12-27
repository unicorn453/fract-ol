/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:07:08 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/08 16:04:23 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "ft_printf/ft_printf.h"
# include "minilibx_opengl_20191021/mlx.h"
# include <limits.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define KEY_ESC 53
# define KEY_PLUS 43
# define KEY_MINUS 45
# define KEY_R 15
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define WIN_WIDTH 600
# define WIN_HEIGHT 600
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_6 22
# define KEY_7 26

typedef struct s_complex
{
	double		real;
	double		imaginary;
}				t_complex;

struct			s_col_name
{
	char		*name;
	int			color;
};

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	int			width;
	int			height;

	double		zoom;
	double		complex_x;
	double		complex_y;

	int			x;
	int			y;

	int			max_iterations;
	int			num_color;

	char		*name;

	t_complex	c;
	t_complex	z;
}				t_data;

//moves.c
int				handle_key(int key, t_data *fractal);

int				handle_mouse(int button, int x, int y, t_data *data);
void			zoom_in(t_data *data);
void			zoom_out(t_data *data);
void			handle_keypress(int keycode, t_data *fractal);

//main.c
void			print_usage(void);
int				handle_julia(char **argv);
int				main(int argc, char **argv);
void			*ft_memset(void *s, int c, size_t n);

//helper functions
int				close_window(t_data *data);
int				ft_strcmp(const char *s1, const char *s2);

t_data			*initialize_fractal(char **name);
void			usual_initializations(t_data *fractal, char **name);
void			*initialize(char **name);

//functions from draw_set.c
void			draw_set(t_data *fractal);
int				get_color_by_name(char *name);
void			setup_hooks_and_loop(t_data *fractal);
void			put_pixel(t_data *fractal, int x, int y, int color);
int				pre_defined_colors(int num_color);

//burningship.c
void			create_burningship(t_data *fractal);
int				burning_ship(t_data *fractal);
int				clamp(int value, int min, int max);
int				color_gradient_palette(int iteration, int max_iterations,
					t_data *fractal);
void			draw_pixel(t_data *fractal, int x, int y);

//julia.c
int				initialize_julia(char **name, char **real, char **imaginary);
void			create_julia(t_data *fractal);
int				calculate_color(t_data *fractal, int n);
void			set_complex_values(t_data *fractal, int x, int y);
int				julia(t_data *fractal);

//mandelbrot.c
double			magnitude(double real, double imaginary);
void			create_mandelbrot(t_data *fractal);

int				mandelbrot(t_data *fractal);
int				get_color(t_data *fractal, int n);
void			set_complex_coordinates(t_data *fractal, int x, int y);

//ft_atof.c
double			ft_atof(char *str);

#endif
