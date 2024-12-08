/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:45:56 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/08 16:12:26 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*comp1;
	unsigned char	*comp2;

	i = 0;
	comp1 = (unsigned char *)s1;
	comp2 = (unsigned char *)s2;
	while (comp1[i] != '\0' || comp2[i] != '\0')
	{
		if (comp1[i] != comp2[i])
			return (comp1[i] - comp2[i]);
		i++;
	}
	return (0);
}

t_data	*initialize_fractal(char **name)
{
	t_data	*fractal;

	fractal = (t_data *)malloc(sizeof(t_data));
	if (!fractal)
	{
		perror("Error: Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	fractal->name = *name;
	usual_initializations(fractal, name);
	return (fractal);
}

void	usual_initializations(t_data *fractal, char **name)
{
	fractal->mlx = mlx_init();
	fractal->win = mlx_new_window(fractal->mlx, WIN_WIDTH, WIN_HEIGHT, *name);
	fractal->img = mlx_new_image(fractal->mlx, WIN_WIDTH, WIN_HEIGHT);
	fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bits_per_pixel,
			&fractal->line_length, &fractal->endian);
	fractal->max_iterations = 50;
	fractal->num_color = 0;
	fractal->x = 0;
	fractal->y = 0;
	fractal->width = WIN_WIDTH;
	fractal->height = WIN_HEIGHT;
	fractal->zoom = 1;
	fractal->complex_x = 0;
	fractal->complex_y = 0;
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data);
	exit(0);
	return (0);
}

void	*initialize(char **name)
{
	t_data	*fractal;

	fractal = (t_data *)malloc(sizeof(t_data));
	if (!fractal)
	{
		perror("Error: Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	fractal->name = *name;
	usual_initializations(fractal, name);
	if (ft_strcmp(*name, "mandelbrot") == 0 || ft_strcmp(*name,
			"burning_ship") == 0)
		draw_set(fractal);
	else
	{
		ft_printf("Error: Unsupported fractal type '%s'.\n", *name);
		free(fractal);
		exit(EXIT_FAILURE);
	}
	mlx_hook(fractal->win, 2, 1L << 0, handle_key, fractal);
	mlx_hook(fractal->win, 4, 1L << 2, handle_mouse, fractal);
	mlx_hook(fractal->win, 17, 0, close_window, fractal);
	mlx_loop(fractal->mlx);
	return (NULL);
}
