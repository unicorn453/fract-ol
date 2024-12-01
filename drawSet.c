/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawSet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:06:08 by kruseva           #+#    #+#             */
/*   Updated: 2024/11/30 14:00:43 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mandelbrot.h" 


struct s_col_name {
    char *name;
    int color;
};


extern struct s_col_name mlx_col_name[];

int get_color_by_name(char *name)
{
    for (int i = 0; mlx_col_name[i].name != 0; i++)
    {
        if (strcmp(mlx_col_name[i].name, name) == 0)
            return mlx_col_name[i].color;
    }
    return -1;
}

int preDefinedColors(int numColor)
{
    if (numColor == 0)
        return get_color_by_name("black");
    if (numColor == 1)
        return get_color_by_name("blue");
    if (numColor == 2)
        return get_color_by_name("green");
    if (numColor == 3)
        return get_color_by_name("red");
    if (numColor == 4)
        return get_color_by_name("yellow");
    if (numColor == 5)
        return get_color_by_name("cyan");

    return 0;
}

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
    return (0);
}

int drawSet(char **set)
{
    t_data data;
    data.numColor = 1;
    printf("Initializing MiniLibX\n");
    data.mlx = mlx_init();
    if (data.mlx == NULL)
    {
        printf("Error: mlx_init failed\n");
        return 1;
    }
    printf("Creating window\n");
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Mandelbrot Set");
    if (data.win == NULL)
    {
        printf("Error: mlx_new_window failed\n");
        return 1;
    }
    mlx_key_hook(data.win, handle_key, &data);
    mlx_mouse_hook(data.win, handle_mouse, &data);

    mlx_hook(data.win, 17, 0, close_window, &data); // Handle window close event
    printf("set: %s\n", *set);
    if (strcmp(*set, "mandelbrot") == 0)
    {
        data.x = -2.0;
        data.y = -2.0;
        data.width = WIN_WIDTH;
        data.height = WIN_HEIGHT;
        data.maxIterations = 600;
        createMandelbrot(&data);
        mlx_loop(data.mlx);
    }
    else
    {
        printf("Invalid set name\n");
        return 1;
    }
    return 0;
}