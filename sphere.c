/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:21:25 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 14:21:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "function_maths.h"

static double	calculate_t(t_sphere *s, t_ray *r)
{
	double	tab[6];
	t_coord sub;

	ft_vectors_substract(&s->origin, &r->origin, &sub);
	tab[0] = 2 * ft_scal_produce(&r->direction, &sub);
	tab[1] = ft_norm2(&sub) - pow(s->rayon, 2);
	tab[2] = pow(tab[0], 2) - 4 * tab[1];
	if (tab[2] < 0)
		return (-1);
	tab[3] = (-tab[0] - sqrt(tab[2])) / 2;
	tab[4] = (-tab[0] + sqrt(tab[2])) / 2;
	if (tab[4] < 0)
		return (-1);
	if (tab[3] > 0)
		return (tab[3]);
	else
		return (tab[4]);
}

double			intersection_sphere(t_sphere *s, t_ray *r
, t_point *base, double *t_min)
{
	double	t;
	t_coord mult;

	t = calculate_t(s, r);
	if (t == -1 || (*t_min != -1 && t > *t_min))
		return (-1);
	else
		*t_min = t;
	if (base == NULL)
		return (0);
	ft_vectors_mult(&r->direction, t, &mult);
	ft_vectors_add(&r->origin, &mult, &base->pos);
	ft_vectors_substract(&s->origin, &base->pos, &base->normal);
	ft_normalize(&base->normal);
	base->rgb.r = s->rgb.r;
	base->rgb.g = s->rgb.g;
	base->rgb.b = s->rgb.b;
	return (1);
}
