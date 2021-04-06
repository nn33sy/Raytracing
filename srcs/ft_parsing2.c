#include "minirt.h"

int		ft_r(char *line, t_scene *scene)
{
	scene->r_x = ft_atoi_rt(line);
	if (scene->r_x == -999)
		return (-1);
	while (*line >= '0' && *line <= '9')
		line++;
	scene->r_y = ft_atoi_rt(line);
	if (scene->r_y == -999)
		return (-1);
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
	if (line == NULL)
		return (NULL);
	if ((coord->x = ft_atoi_rt(line)) == -999)
		return (NULL);
	while (*line && *line != ',')
		line++;
	if (!(*line))
		return (NULL);
	line++;
	if ((coord->y = ft_atoi_rt(line)) == -999)
		return (NULL);
	while (*line && *line != ',')
		line++;
	if (!(*line))
		return (NULL);
	line++;
	if ((coord->z = ft_atoi_rt(line)) == -999)
		return (NULL);
	while (*line && (((*line >= '0') && (*line <= '9'))
	|| (*line == '.') || (*line == '-')))
		line++;
	return (line);
}

char	*ft_parsing_rgb(t_rgb *rgb, char *line)
{
	if (line == NULL)
		return (NULL);
	if ((rgb->r = ft_atoi_rt(line)) == -999)
		return (NULL);
	while (*line && (*line != ','))
		line++;
	if (!(*line))
		return (NULL);
	line++;
	if ((rgb->g = ft_atoi_rt(line)) == -999)
		return (NULL);
	while (*line && (*line != ','))
		line++;
	if (!(*line))
		return (NULL);
	line++;
	if ((rgb->b = ft_atoi_rt(line)) == -999)
		return (NULL);
	while (*line && ((*line >= '0') && (*line <= '9')))
		line++;
	return (line);
}

int		ft_a(char *line, t_scene *scene)
{
	line = ft_parsing_double(line, &scene->amb_light.ratio);
	if (line == NULL)
		return (-1);
	line = ft_parsing_rgb(&scene->amb_light.rgb, line);
	if (line == NULL)
		return (-1);
	return (1);
}

int		ft_l(char *line, t_light **light)
{
	t_light *l;

	l = (t_light *)malloc(sizeof(t_light));
	if (l == NULL)
		return (-1);
	l->next = *light;
	*light = l;
	line = ft_parsing_position(line, &l->pos);
	if (line == NULL)
		return (-1);
	line = ft_parsing_double(line, &l->i);
	if (line == NULL)
		return (-1);
	line = ft_parsing_rgb(&l->rgb, line);
	if (line == NULL)
		return (-1);
	return (1);
}
