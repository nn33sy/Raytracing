/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ombre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:03:09 by how-choongi       #+#    #+#             */
/*   Updated: 2021/04/07 19:03:10 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_ombre_2(t_scene *scene, double dist, t_ray ray)
{
	double	ti;
	t_list	*ptn;

	ti = -1;
	ptn = *(scene->list);
	while (ptn != NULL)
	{
		if (ptn->type == 0 && (intersection_sphere((t_sphere *)ptn->object,
					&ray, NULL, &ti) == 0) && (ti * ti < dist))
			return (0);
		if (ptn->type == 1 && (intersection_plan((t_plan *)ptn->object,
					&ray, NULL, &ti) == 0) && (ti * ti < dist))
			return (0);
		if (ptn->type == 2 && (intersection_square((t_square *)ptn->object,
					&ray, NULL, &ti) == 0) && (ti * ti < dist))
			return (0);
		if (ptn->type == 3 && (ft_intersection_triangle((t_triangle *)
					ptn->object, &ray, NULL, &ti) == 0) && (ti * ti < dist))
			return (0);
		if (ptn->type == 4 && (ft_intersection_cylinder((t_cylinder *)
					ptn->object, &ray, NULL, &ti) == 0) && (ti * ti < dist))
			return (0);
		ptn = ptn->next;
	}
	return (1);
}

float	ft_ombre(t_point *base, double dist, t_scene *scene, t_light *light)
{
	t_ray	ray_reflect;

	ft_vectors_substract(&base->pos, &light->pos, &ray_reflect.direction);
	ft_normalize(&ray_reflect.direction);
	ft_vectors_mult(&base->normal, 0.001, &ray_reflect.origin);
	ft_vectors_add(&ray_reflect.origin, &base->pos, &ray_reflect.origin);
	return (ft_ombre_2(scene, dist, ray_reflect));
}
