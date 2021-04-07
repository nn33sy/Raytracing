/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection_cylinder.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:24:01 by user42            #+#    #+#             */
/*   Updated: 2021/04/07 19:02:57 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	ft_intersection_cylinder_3(t_cylinder *cy,
t_ray *ray, double *t0, double *t1)
{
	double	delta[4];
	t_coord tmp;

	ft_vectors_substract(&cy->base, &ray->origin, &tmp);
	ft_normalize(&cy->direction);
	delta[0] = ft_scal_produce(&ray->direction, &ray->direction) -
	pow(ft_scal_produce(&ray->direction, &cy->direction), 2);
	delta[1] = 2 * (ft_scal_produce(&ray->direction, &tmp) -
	(ft_scal_produce(&ray->direction, &cy->direction)
	* ft_scal_produce(&tmp, &cy->direction)));
	delta[2] = ft_scal_produce(&tmp, &tmp) - pow(ft_scal_produce(&tmp,
	&cy->direction), 2) - pow((cy->diameter / 2), 2);
	delta[3] = pow(delta[1], 2) - (4 * delta[0] * delta[2]);
	if (delta[3] <= 0)
		return (-1);
	*t0 = (-delta[1] - sqrt(delta[3])) / (2 * delta[0]);
	*t1 = (-delta[1] + sqrt(delta[3])) / (2 * delta[0]);
	if (*t0 <= 0 && *t1 <= 0)
		return (-1);
	return (1);
}

static double	ft_intersection_cylinder_2(t_cylinder *cy
, t_ray *ray, double *m_f, double *t_f)
{
	double	t[2];
	double	height[2];
	t_coord	tmp;

	ft_vectors_substract(&cy->base, &ray->origin, &tmp);
	if (ft_intersection_cylinder_3(cy, ray, &t[0], &t[1]) == -1)
		return (-1);
	height[0] = ft_scal_produce(&ray->direction, &cy->direction)
	* t[0] + ft_scal_produce(&tmp, &cy->direction);
	height[1] = ft_scal_produce(&ray->direction, &cy->direction)
	* t[1] + ft_scal_produce(&tmp, &cy->direction);
	if (t[0] >= 0 && t[0] <= t[1] && height[0] >= 0 && height[0] <= cy->height)
	{
		*m_f = height[0];
		*t_f = t[0];
	}
	else if (t[1] >= 0 && height[1] >= 0 && height[1] <= cy->height)
	{
		*m_f = height[1];
		*t_f = t[1];
	}
	else
		return (-1);
	return (1);
}

int				ft_intersection_cylinder(t_cylinder *cy
, t_ray *ray, t_point *base, double *t_min)
{
	double	m;
	double	t;
	t_coord	tmp;

	if (ft_intersection_cylinder_2(cy, ray, &m, &t) == -1)
		return (-1);
	if (*t_min != -1 && t > *t_min)
		return (-1);
	*t_min = t;
	if (base == NULL)
		return (0);
	ft_vectors_mult(&ray->direction, t, &base->pos);
	ft_vectors_add(&base->pos, &ray->origin, &base->pos);
	ft_vectors_substract(&cy->base, &base->pos, &tmp);
	ft_vectors_mult(&cy->direction, m, &base->normal);
	ft_vectors_substract(&base->normal, &tmp, &base->normal);
	ft_normalize(&base->normal);
	base->rgb.r = cy->rgb.r;
	base->rgb.g = cy->rgb.g;
	base->rgb.b = cy->rgb.b;
	return (1);
}
