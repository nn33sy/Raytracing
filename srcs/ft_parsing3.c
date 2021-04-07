/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:03:21 by how-choongi       #+#    #+#             */
/*   Updated: 2021/04/07 19:03:22 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_c(char *line, t_camera **camera)
{
	t_camera *c;

	if ((c = (t_camera *)malloc(sizeof(t_camera))) == NULL)
		return (-1);
	c->next = NULL;
	if (*camera != NULL)
	{
		(*camera)->before = c;
		c->next = *camera;
	}
	c->before = NULL;
	*camera = c;
	if ((line = ft_parsing_position(line, &c->ray.origin)) == NULL)
		return (-1);
	if ((line = ft_parsing_position(line, &c->direction)) == NULL)
		return (-1);
	if ((line = ft_parsing_double(line, &c->fov)) == NULL)
		return (-1);
	if (c->fov < 0)
		c->fov *= -1;
	c->fov = (c->fov * 3.14) / 180;
	return (1);
}

int		ft_sp(char *line, t_scene *scene)
{
	t_sphere *sphere;

	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (-1);
	ft_lstadd_front(scene->list, ft_lstnew((void *)sphere, 0));
	if ((line = ft_parsing_position(line, &sphere->origin)) == NULL)
		return (-1);
	if ((line = ft_parsing_double(line, &sphere->rayon)) == NULL)
		return (-1);
	sphere->rayon /= 2;
	if ((line = ft_parsing_rgb(&sphere->rgb, line)) == NULL)
		return (-1);
	(*(scene->list))->magic = ft_atoi_rt(line);
	return (1);
}

int		ft_p(char *line, t_scene *scene)
{
	t_plan *plan;

	if ((plan = malloc(sizeof(t_plan))) == NULL)
		return (-1);
	ft_lstadd_front(scene->list, ft_lstnew((void *)plan, 1));
	if ((line = ft_parsing_position(line, &plan->center)) == NULL)
		return (-1);
	if ((line = ft_parsing_position(line, &plan->direction)) == NULL)
		return (-1);
	if ((line = ft_parsing_rgb(&plan->rgb, line)) == NULL)
		return (-1);
	(*(scene->list))->magic = ft_atoi_rt(line);
	return (1);
}

int		ft_sq(char *line, t_scene *scene)
{
	t_square *square;

	if ((square = malloc(sizeof(t_square))) == NULL)
		return (-1);
	ft_lstadd_front(scene->list, ft_lstnew((void *)square
	, 2));
	if ((line = ft_parsing_position(line, &square->center)) == NULL)
		return (-1);
	if ((line = ft_parsing_position(line, &square->direction)) == NULL)
		return (-1);
	if ((line = ft_parsing_double(line, &square->side_size)) == NULL)
		return (-1);
	if ((line = ft_parsing_rgb(&square->rgb, line)) == NULL)
		return (-1);
	(*(scene->list))->magic = ft_atoi_rt(line);
	return (1);
}

int		ft_tr(char *line, t_scene *scene)
{
	t_triangle *triangle;

	if ((triangle = malloc(sizeof(t_triangle))) == NULL)
		return (-1);
	ft_lstadd_front(scene->list, ft_lstnew((void *)triangle
	, 3));
	if ((line = ft_parsing_position(line, &triangle->first)) == NULL)
		return (-1);
	if ((line = ft_parsing_position(line, &triangle->second)) == NULL)
		return (-1);
	if ((line = ft_parsing_position(line, &triangle->third)) == NULL)
		return (-1);
	if ((line = ft_parsing_rgb(&triangle->rgb, line)) == NULL)
		return (-1);
	(*(scene->list))->magic = ft_atoi_rt(line);
	return (1);
}
