/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:03:54 by how-choongi       #+#    #+#             */
/*   Updated: 2021/04/07 19:03:55 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_clean_rgb(t_palette *color_f)
{
	color_f->rgb.r = 0;
	color_f->rgb.g = 0;
	color_f->rgb.b = 0;
	color_f->intensity = 0;
}

double	ft_determinant_matrix(t_matrix_two *matrix)
{
	return ((matrix->x1 * matrix->y2) - (matrix->x2 * matrix->y1));
}
