/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <how-choongines@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 13:31:46 by user42            #+#    #+#             */
/*   Updated: 2021/04/03 19:53:02 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_r(char *line, t_scene *scene)
{
	if (*line == 'R')
		line++;
	else
		return (-1);
	scene->r_x = ft_atoi_rt(line);
	while (*line >= '0' && *line <= '9')
		line++;
	scene->r_y = ft_atoi_rt(line);
	if (scene->r_x < 0 || scene->r_y < 0)
	{
		scene->r_x = 400;
		scene->r_y = 400;
	}
	scene->ratio = scene->r_x / scene->r_y;
	return (1);
}

char	*ft_parsing_position(char *line, t_coord *coord)
{
	coord->x = ft_atoi_rt(line);
	while (*line && *line != ',')
		line++;
	if (*line)
		line++;
	coord->y = ft_atoi_rt(line);
	while (*line && *line != ',')
		line++;
	if (*line)
		line++;
	coord->z = ft_atoi_rt(line);
	while (*line && (((*line >= '0') && (*line <= '9'))
	|| (*line == '.') || (*line == '-')))
		line++;
	return (line);
}

char	*ft_parsing_rgb(t_rgb *rgb, char *line)
{
	rgb->r = ft_atoi_rt(line);
	while (*line && (*line != ','))
		line++;
	if (*line)
		line++;
	rgb->g = ft_atoi_rt(line);
	while (*line && (*line != ','))
		line++;
	if (*line)
		line++;
	rgb->b = ft_atoi_rt(line);
	while (*line && ((*line >= '0') && (*line <= '9')))
		line++;
	return (line);
}

int		ft_a(char *line, t_scene *scene)
{
	if (*line == 'A')
		line++;
	else
		return (-1);
	line = ft_parsing_double(line, &scene->amb_light.ratio);
	ft_parsing_rgb(&scene->amb_light.rgb, line);
	return (1);
}

int		ft_l(char *line, t_light **light)
{
	t_light *l;

	if (*line != 'l')
		return (-1);
	line++;
	l = (t_light *)malloc(sizeof(t_light));
	if (l == NULL)
		return (-1);
	line = ft_parsing_position(line, &l->pos);
	line = ft_parsing_double(line, &l->i);
	ft_parsing_rgb(&l->rgb, line);
	l->next = *light;
	*light = l;
	return (1);
}

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
	return (1);
}

char	*ft_parsing_double(char *line, double *nb)
{
	while (*line && (*line == ' '))
		line++;
	*nb = ft_atoi_rt(line);
	while (*line && ((*line >= '0' && *line <= '9') || (*line == '.')))
		line++;
	return (line);
}

int		ft_cy(char *line, t_scene *scene)
{
	t_cylinder *cylinder;

	if (*line != 'c')
		return (-1);
	line++;
	if (*line != 'y')
		return (-1);
	line++;
	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return (-1);
	line = ft_parsing_position(line, &cylinder->base);
	line = ft_parsing_position(line, &cylinder->direction);
	line = ft_parsing_rgb(&cylinder->rgb, line);
	line = ft_parsing_double(line, &cylinder->diameter);
	line = ft_parsing_double(line, &cylinder->height);
	ft_lstadd_front(scene->list, ft_lstnew((void *)cylinder
	, 4, ft_atoi_rt(line)));
	return (1);
}

int	ft_parsing_line(char *line, t_scene *scene)
{
	int res;

	res = 0;
	if (line[0] == 'R')
		res = ft_r(line, scene);
	if (line[0] == 's' && line[1] == 'p')
		res = ft_sp(line, scene);
	if (line[0] == 's' && line[1] == 'q')
		res = ft_sq(line, scene);
	if (line[0] == 'p')
		res = ft_p(line, scene);
	if (line[0] == 't' && line[1] == 'r')
		res = ft_tr(line, scene);
	if (line[0] == 'c' && line[1] == 'y')
		res = ft_cy(line, scene);
	if (line[0] == 'A')
		res = ft_a(line, scene);
	if (line[0] == 'c' && line[1] == ' ')
		res = ft_c(line, scene->camera);
	if (line[0] == 'l')
		res = ft_l(line, scene->light);
	return (res);
}

static void ft_close_error(t_scene *scene, int fd)
{
	ft_clean_scene(scene);
	ft_putstr_fd("Error in the file or doesn't allocate", 1);
	free(scene);
	close(fd);
}

t_scene	*main_parsing(char *file_scene)
{
	char	**line;
	int		fd;
	t_scene	*scene;

	fd = open(file_scene, O_RDONLY);
	line = (char**)malloc(sizeof(char *));
	if (line == NULL)
		return (NULL);
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->light = malloc(sizeof(t_light *));
	*(scene->light) = NULL;
	scene->list = malloc(sizeof(t_list *));
	*(scene->list) = NULL;
	scene->camera = malloc(sizeof(t_camera *));
	*(scene->camera) = NULL;
	if (!scene || !(scene->light) || !(scene->list) || !(scene->camera))
	{
		ft_close_error(scene, fd);
		return (NULL);
	}
	while (get_next_line(fd, line) > 0)
	{
		if (ft_parsing_line(*line, scene) == -1)
		{
			ft_close_error(scene, fd);
			return (NULL);
		}
		free (*line);
	}
	if (ft_parsing_line(*line, scene) == -1)
		{
			ft_close_error(scene, fd);
			return (NULL);
		}
	free(*line);
	free(line);
	close(fd);
	return (scene);
}
