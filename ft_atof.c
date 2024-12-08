/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:57:11 by kruseva           #+#    #+#             */
/*   Updated: 2024/12/07 19:42:23 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

double	check_exponent(char *str, double result)
{
	int	exp_sign;
	int	exponent;

	exp_sign = 1;
	exponent = 0;
	if (*str == 'e' || *str == 'E')
	{
		str++;
		if (*str == '-')
		{
			exp_sign = -1;
			str++;
		}
		else if (*str == '+')
		{
			str++;
		}
		while (*str && ft_isdigit(*str))
		{
			exponent = exponent * 10 + (*str - '0');
			str++;
		}
		result *= pow(10, exp_sign * exponent);
	}
	return (result);
}

char	*check_sign(char *str, double *sign)
{
	*sign = 1.0;
	if (*str == '-')
	{
		*sign = -1.0;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	return (str);
}

char	*check_decimal(char *str, double *result, double *decimal_place,
		int *decimal_point)
{
	if (*str == '.')
	{
		*decimal_point = 1;
		str++;
	}
	if (*decimal_point)
	{
		while (*str && ft_isdigit(*str))
		{
			*result += (*str - '0') * *decimal_place;
			*decimal_place /= 10;
			str++;
		}
	}
	return (str);
}

double	ft_atof(char *str)
{
	double	result;
	double	sign;
	double	decimal_place;
	int		decimal_point;

	result = 0.0;
	sign = 1.0;
	decimal_place = 0.1;
	decimal_point = 0;
	str = check_sign(str, &sign);
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	str = check_decimal(str, &result, &decimal_place, &decimal_point);
	result = check_exponent(str, result);
	return (result * sign);
}
