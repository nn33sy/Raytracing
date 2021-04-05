#include "minirt.h"

int		ft_c(char *line, t_camera **camera)
{
	t_camera *c;

	line++;
	c = (t_camera *)malloc(sizeof(t_camera));
	(void)camera;
	if (c == NULL)
		return (-1);
	line = ft_parsing_position(line, &c->ray.origin);
	line = ft_parsing_position(line, &c->direction);
	line = ft_parsing_double(line, &c->fov);
	if (line == NULL)
		return (-1);
	if (c->fov < 0)
		c->fov *= -1;
	c->fov = (c->fov * 3.14) / 180;
	c->next = NULL;
	if (*camera != NULL)
	{
		(*camera)->before = c;
		c->next = *camera;
	}
	c->before = NULL;
	*camera = c;
	return (1);
}

int		ft_sp(char *line, t_scene *scene)
{
	t_sphere *sphere;

	if (*line != 's')
		return (-1);
	line++;
	if (*line != 'p')
		return (-1);
	line++;
	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (-1);
	line = ft_parsing_position(line, &sphere->origin);
	line = ft_parsing_double(line, &sphere->rayon);
	sphere->rayon /= 2;
	line = ft_parsing_rgb(&sphere->rgb, line);
	ft_lstadd_front(scene->list, ft_lstnew((void *)sphere, 0,
	ft_atoi_rt(line)));
	if (line == NULL)
		return (-1);
	return (1);
}

int		ft_p(char *line, t_scene *scene)
{
	t_plan *plan;

	if (*line != 'p')
		return (-1);
	line++;
	if (*line != 'l')
		return (-1);
	line++;
	plan = malloc(sizeof(t_plan));
	if (plan == NULL)
		return (-1);
	line = ft_parsing_position(line, &plan->center);
	line = ft_parsing_position(line, &plan->direction);
	line = ft_parsing_rgb(&plan->rgb, line);
	ft_lstadd_front(scene->list, ft_lstnew((void *)plan, 1, ft_atoi_rt(line)));
	if (line == NULL)
		return (-1);
	return (1);
}

int		ft_sq(char *line, t_scene *scene)
{
	t_square *square;

	if (*line != 's')
		return (-1);
	line++;
	if (*line != 'q')
		return (-1);
	line++;
	square = malloc(sizeof(t_square));
	if (square == NULL)
		return (-1);
	line = ft_parsing_position(line, &square->center);
	line = ft_parsing_position(line, &square->direction);
	line = ft_parsing_double(line, &square->side_size);
	line = ft_parsing_rgb(&square->rgb, line);
	ft_lstadd_front(scene->list, ft_lstnew((void *)square
	, 2, ft_atoi_rt(line)));
	if (line == NULL)
		return (-1);
	return (1);
}

int		ft_tr(char *line, t_scene *scene)
{
	t_triangle *triangle;

	if (*line != 't')
		return (-1);
	line++;
	if (*line != 'r')
		return (-1);
	line++;
	triangle = malloc(sizeof(t_triangle));
	if (triangle == NULL)
		return (-1);
	line = ft_parsing_position(line, &triangle->first);
	line = ft_parsing_position(line, &triangle->second);
	line = ft_parsing_position(line, &triangle->third);
	line = ft_parsing_rgb(&triangle->rgb, line);
	ft_lstadd_front(scene->list, ft_lstnew((void *)triangle
	, 3, ft_atoi_rt(line)));
	if (line == NULL)
		return (-1);
	return (1);
}
