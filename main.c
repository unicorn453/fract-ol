/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:30:50 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/08 19:59:20 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


// Function to check memory leaks
void check_system_memory_leaks(void)
{
    system("leaks fractol");
}

// Setup memory leak checker
void setup_memory_leak_checker(void)
{
    if (atexit(check_system_memory_leaks) != 0)
    {
        fprintf(stderr, "Failed to register memory leak checker.\n");
    }
}


void	*ft_memset(void *s, int c, size_t n)
{
	char	*newarray;
	char	value;
	size_t	i;

	newarray = s;
	value = (char)c;
	i = 0;
	while (i < n)
	{
		newarray[i] = value;
		i++;
	}
	return (s);
}

void	print_usage(void)
{
	ft_printf("Usage: ./fractol mandelbrot\n");
	ft_printf("Usage: ./fractol julia real_num imaginary_num\n");
	ft_printf("List fractals: julia, mandelbrot, burning_ship\n");
}

int	handle_julia(char **argv)
{
	if (argv[2] == NULL || argv[3] == NULL)
	{
		ft_printf("Usage: ./fractol [julia] real_num imaginary_num\n");
		exit(EXIT_FAILURE);
	}
	if (initialize_julia(&argv[1], &argv[2], &argv[3]) != 0)
	{
		perror("Error: initialize_julia failed");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{

	setup_memory_leak_checker();
	if (argc < 2)
	{
		print_usage();
		return (1);
	}
	if (ft_strcmp(argv[1], "mandelbrot") == 0 || ft_strcmp(argv[1],
			"burning_ship") == 0)
	{
		if (initialize(&argv[1]) != 0)
		{
			ft_printf("Error: initialize failed\n");
			return (1);
		}
	}
	else if (ft_strcmp(argv[1], "julia") == 0)
		return (handle_julia(argv));
	else
	{
		ft_printf("Error: Unsupported fractal type '%s'.\n", argv[1]);
		return (1);
	}
	return (0);
}
