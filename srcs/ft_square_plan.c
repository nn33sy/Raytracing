/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square_plan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 13:40:58 by user42            #+#    #+#             */
/*   Updated: 2021/04/01 16:40:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


double	intersection_basic(t_ray *ray, t_coord *direction, t_coord *center)
{
	double	t;
	t_coord a;
	double	essai;

	if (ft_scal_produce(&(ray->direction), direction) == 0)
		return (-1);
	essai = ft_scal_produce(&(ray->direction), direction) /
	(sqrt(ft_norm2(&ray->direction)) * sqrt(ft_norm2(direction)));
	essai = acos(essai) * (180 / PI);
	ft_vectors_substract(&(ray->origin), center, &a);
	t = ft_scal_produce(&a, direction);
	t /= ft_scal_produce(&(ray->direction), direction);
	if (t > 0)
		return (t);
	return (-1);
}

int		intersection_plan(t_plan *plan, t_ray *ray
, t_point *base, double *t_min)
{
	double t;

	t = intersection_basic(ray, &(plan->direction), &(plan->center));
	if (t == -1)
		return (-1);
	if (*t_min != -1 && t > *t_min)
		return (-1);
	*t_min = t;
	if (base == NULL)
		return (0);
	ft_coord(plan->direction.x, plan->direction.y
	, plan->direction.z, &base->normal);
	ft_vectors_mult(&(ray->direction), t, &base->pos);
	ft_vectors_add(&base->pos, &(ray->origin), &base->pos);
	base->rgb.r = plan->rgb.r;
	base->rgb.g = plan->rgb.g;
	base->rgb.b = plan->rgb.b;
	return (1);
}

int		intersection_square(t_square *square, t_ray *ray
, t_point *base, double *t_min)
{
	double	t;
	t_coord	proj;

	t = intersection_basic(ray, &(square->direction), &(square->center));
	if (t == -1 && *t_min != -1 && t > *t_min)
		return (-1);
	ft_vectors_mult(&(ray->direction), t, &proj);
	ft_vectors_add(&proj, &(ray->origin), &proj);
	if (ft_abs(proj.x - square->center.x) > (square->side_size) / 2)
		return (-1);
	if (ft_abs(proj.y - square->center.y) > (square->side_size) / 2)
		return (-1);
	if (ft_abs(proj.z - square->center.z) > (square->side_size) / 2)
		return (-1);
	*t_min = t;
	if (base == NULL)
		return (0);
	ft_coord(square->direction.x, square->direction.y
	, square->direction.z, &base->normal);
	ft_coord(proj.x, proj.y, proj.z, &base->pos);
	base->rgb.r = square->rgb.r;
	base->rgb.g = square->rgb.g;
	base->rgb.b = square->rgb.b;
	return (1);
}
