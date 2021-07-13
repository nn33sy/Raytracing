/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:52:42 by how-choon         #+#    #+#             */
/*   Updated: 2021/04/09 14:29:37 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_r(char *line, t_scene *scene)
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
	if (scene->r_x % 2 == 1)
		scene->r_x += 1;
	if (scene->r_y % 2 == 1)
		scene->r_y += 1;
	scene->ratio = scene->r_x / scene->r_y;
	return (1);
}

char	*ft_parsing_position(char *line, t_coord *coord)
{
	if (line == NULL)
		return (NULL);
	coord->x = ft_atoi_rt(line);
	if (coord->x == -999)
		return (NULL);
	while (*line && *line != ',')
		line++;
	if (!(*line))
		return (NULL);
	line++;
	coord->y = ft_atoi_rt(line);
	if (coord->y == -999)
		return (NULL);
	while (*line && *line != ',')
		line++;
	if (!(*line))
		return (NULL);
	line++;
	coord->z = ft_atoi_rt(line);
	if (coord->z == -999)
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
	rgb->r = ft_atoi_rt(line);
	if (rgb->r == -999)
		return (NULL);
	while (*line && (*line != ','))
		line++;
	if (!(*line))
		return (NULL);
	line++;
	rgb->g = ft_atoi_rt(line);
	if (rgb->g == -999)
		return (NULL);
	while (*line && (*line != ','))
		line++;
	if (!(*line))
		return (NULL);
	line++;
	rgb->b = ft_atoi_rt(line);
	if (rgb->b == -999)
		return (NULL);
	while (*line && ((*line >= '0') && (*line <= '9')))
		line++;
	return (line);
}

int	ft_a(char *line, t_scene *scene)
{
	line = ft_parsing_double(line, &scene->amb_light.ratio);
	if (line == NULL)
		return (-1);
	line = ft_parsing_rgb(&scene->amb_light.rgb, line);
	if (line == NULL)
		return (-1);
	return (ft_empty_line(line));
}

int	ft_l(char *line, t_light **light)
{
	t_light	*l;

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
	return (ft_empty_line(line));
}
