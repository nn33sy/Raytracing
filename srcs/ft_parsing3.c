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

void	ft_cbis(t_camera *c, t_camera **camera)
{
	c->next = NULL;
	if (*camera != NULL)
	{
		(*camera)->before = c;
		c->next = *camera;
	}
	c->before = NULL;
	*camera = c;
}

int	ft_c(char *line, t_camera **camera)
{
	t_camera	*c;

	c = (t_camera *)malloc(sizeof(t_camera));
	if (c == NULL)
		return (-1);
	ft_cbis(c, camera);
	line = ft_parsing_position(line, &c->ray.origin);
	if (line == NULL)
		return (-1);
	line = ft_parsing_position(line, &c->direction);
	if (line == NULL)
		return (-1);
	line = ft_parsing_double(line, &c->fov);
	if (line == NULL)
		return (-1);
	if (c->fov < 0)
		c->fov *= -1;
	c->fov = (c->fov * 3.14) / 180;
	return (ft_empty_line(line));
}

int	ft_sp(char *line, t_scene *scene)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (-1);
	ft_lstadd_front(scene->list, ft_lstnew((void *)sphere, 0));
	line = ft_parsing_position(line, &sphere->origin);
	if (line == NULL)
		return (-1);
	line = ft_parsing_double(line, &sphere->rayon);
	if (line == NULL)
		return (-1);
	sphere->rayon /= 2;
	line = ft_parsing_rgb(&sphere->rgb, line);
	if (line == NULL)
		return (-1);
	(*(scene->list))->magic = ft_atoi_rt(line);
	if ((*(scene->list))-> magic != -999)
		return (0);
	return (1);
}

int	ft_p(char *line, t_scene *scene)
{
	t_plan	*plan;

	plan = malloc(sizeof(t_plan));
	if (plan == NULL)
		return (-1);
	ft_lstadd_front(scene->list, ft_lstnew((void *)plan, 1));
	line = ft_parsing_position(line, &plan->center);
	if (line == NULL)
		return (-1);
	line = ft_parsing_position(line, &plan->direction);
	if (line == NULL)
		return (-1);
	line = ft_parsing_rgb(&plan->rgb, line);
	if (line == NULL)
		return (-1);
	(*(scene->list))->magic = ft_atoi_rt(line);
	return (1);
}

int	ft_sq(char *line, t_scene *scene)
{
	t_square	*square;

	square = malloc(sizeof(t_square));
	if (square == NULL)
		return (-1);
	ft_lstadd_front(scene->list,
		ft_lstnew((void *)square, 2));
	line = ft_parsing_position(line, &square->center);
	if (line == NULL)
		return (-1);
	line = ft_parsing_position(line, &square->direction);
	if (line == NULL)
		return (-1);
	line = ft_parsing_double(line, &square->side_size);
	if (line == NULL)
		return (-1);
	line = ft_parsing_rgb(&square->rgb, line);
	if (line == NULL)
		return (-1);
	(*(scene->list))->magic = ft_atoi_rt(line);
	return (1);
}
