/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:11:43 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/16 18:15:57 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

static int			ft_space(char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || c == '\r'
		|| c == '\n' || c == ' ')
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

double				ft_atoi_rt(const char *str)
{
	int			sign;
	double		res;

	sign = 1;
	res = 0;
	while (*str && ft_space(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
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
