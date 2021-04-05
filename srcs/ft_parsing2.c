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
