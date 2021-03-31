#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "minilibx-linux/mlx.h"
#include "function_maths.h"
#include "get_next_line.h"
#include "libft.h"
#include "parsing.h"
#include "image.h"

double		ft_ombre_2(t_scene *scene, double dist, t_ray ray_reflect)
{
	double	t_inter;
	t_list	*ptn;

	t_inter = -1;
	ptn = *(scene->list);
	while (ptn != NULL)
	{
		if (ptn->type == 0 && (intersection_sphere((t_sphere *)ptn->object,
&ray_reflect, NULL, &t_inter) == 0) && (t_inter * t_inter < dist))
			return (0);
		if (ptn->type == 1 && (intersection_plan((t_plan *)ptn->object,
&ray_reflect, NULL, &t_inter) == 0) && (t_inter * t_inter < dist))
			return (0);
		if (ptn->type == 2 && (intersection_square((t_square *)ptn->object,
&ray_reflect, NULL, &t_inter) == 0) && (t_inter * t_inter < dist))
			return (0);
		if (ptn->type == 3 && (ft_intersection_triangle((t_triangle *)
ptn->object, &ray_reflect, NULL, &t_inter) == 0) && (t_inter * t_inter < dist))
			return (0);
		if (ptn->type == 4 && (ft_intersection_cylinder((t_cylinder *)
ptn->object, &ray_reflect, NULL, &t_inter) == 0) && (t_inter * t_inter < dist))
			return (0);
		ptn = ptn->next;
	}
	return (1);
}

float		ft_ombre(t_point *base, double dist, t_scene *scene, t_light *light)
{
	t_ray	ray_reflect;

	ft_vectors_substract(&base->pos, &light->pos, &ray_reflect.direction);
	ft_normalize(&ray_reflect.direction);
	ft_vectors_mult(&base->normal, 0.001, &ray_reflect.origin);
	ft_vectors_add(&ray_reflect.origin, &base->pos, &ray_reflect.origin);
	return (ft_ombre_2(scene, dist, ray_reflect));
}
