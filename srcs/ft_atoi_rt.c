/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_rt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  user42 <user42@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:11:43 by how-choon         #+#    #+#             */
/*   Updated: 2021/04/06 09:45:07 by  user42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int			ft_space(char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || c == '\r'
		|| c == '\n' || c == ' ' || c == ',' || c == '.')
		return (1);
	return (0);
}

static double		count_nb(const char *str)
{
	int i;

	i = 0;
	while ((str[i] >= '0') && (str[i] <= '9'))
		i++;
	return ((double)i);
}

static void			ft_initialize(int *sign, double *res)
{
	*sign = 1;
	*res = 0;
}

double				ft_atoi_rt(const char *str)
{
	int			sign;
	double		res;

	ft_initialize(&sign, &res);
	while (*str && ft_space(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && ft_space(*str) == 0)
	{
		if (ft_isdigit(*str) == 0)
			return (-999);
		res = res * 10 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		res += ft_atoi_rt(str) * pow(10, -count_nb(str));
	}
	return (sign * res);
}
