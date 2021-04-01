/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mirror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 23:22:48 by how-choongi       #+#    #+#             */
/*   Updated: 2021/04/01 11:54:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mlx.h"
#include "function_maths.h"
#include "get_next_line.h"
#include "libft.h"
#include "parsing.h"
#include "image.h"

void			ft_mirror(t_palette *color, t_ray *ray, t_point *base,
t_scene *scene)
{
	t_ray	mirror;
	t_coord	res;

	ft_vectors_mult(&base->normal, 0.001, &mirror.origin);
	ft_vectors_add(&mirror.origin, &base->pos, &mirror.origin);
	ft_vectors_mult(&base->normal, 2 * ft_scal_produce(&ray->direction,
&base->normal), &res);
	ft_vectors_substract(&res, &ray->direction, &mirror.direction);
	scene->nb_rebond -= 1;
	ft_color_intensity(color, scene, &mirror);
}
