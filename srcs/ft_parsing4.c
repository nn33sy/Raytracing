/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:03:27 by how-choongi       #+#    #+#             */
/*   Updated: 2021/04/07 19:03:28 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_cy(char *line, t_scene *scene)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return (-1);
	ft_lstadd_front(scene->list, ft_lstnew((void *)cylinder, 4));
	line = ft_parsing_position(line, &cylinder->base);
	if (line == NULL)
		return (-1);
	line = ft_parsing_position(line, &cylinder->direction);
	if (line == NULL)
		return (-1);
	line = ft_parsing_double(line, &cylinder->diameter);
	if (line == NULL)
		return (-1);
	line = ft_parsing_double(line, &cylinder->height);
	if (line == NULL)
		return (-1);
	line = ft_parsing_rgb(&cylinder->rgb, line);
	if (line == NULL)
		return (-1);
	(*(scene->list))->magic = ft_atoi_rt(line);
	if ((*(scene->list))-> magic >= 0 && (*(scene->list))-> magic <= 3)
		return (1);
	return (0);
}

int	ft_tr(char *line, t_scene *scene)
{
	t_triangle	*triangle;

	triangle = malloc(sizeof(t_triangle));
	if (triangle == NULL)
		return (-1);
	ft_lstadd_front(scene->list,
		ft_lstnew((void *)triangle, 3));
	line = ft_parsing_position(line, &triangle->first);
	if (line == NULL)
		return (-1);
	line = ft_parsing_position(line, &triangle->second);
	if (line == NULL)
		return (-1);
	line = ft_parsing_position(line, &triangle->third);
	if (line == NULL)
		return (-1);
	line = ft_parsing_rgb(&triangle->rgb, line);
	if (line == NULL)
		return (-1);
	(*(scene->list))->magic = ft_atoi_rt(line);
	if ((*(scene->list))-> magic >= 0 && (*(scene->list))-> magic <= 3)
		return (1);
	return (1);
}

int	ft_empty_line(char *chain)
{
	int	i;

	i = 0;
	while (chain[i] != '\n' && chain[i] != '\0')
	{
		if (chain[i] != ' ' && chain[i] != '\t'
			&& chain[i] != '\v' && chain[i] != '\f' && chain[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}
