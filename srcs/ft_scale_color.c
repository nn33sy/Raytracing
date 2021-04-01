/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scale_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 23:24:51 by how-choongi       #+#    #+#             */
/*   Updated: 2021/04/01 16:40:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	ft_scale_rgb(t_rgb *rgb)
{
	ft_scaling_one_value(&rgb->g);
	ft_scaling_one_value(&rgb->r);
	ft_scaling_one_value(&rgb->b);
}

void	ft_scaling_one_value(double *value)
{
	if (*value > 255)
		*value = 255;
	if (*value < 0)
		*value = 0;
}
