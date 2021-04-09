/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intensity_colors2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:22:36 by how-choongi       #+#    #+#             */
/*   Updated: 2021/04/09 14:25:43 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_color_intensity_4(t_palette *color
, t_scene *scene, t_point base, t_light *tmp)
{
	double	dist;
	t_coord	l;

	ft_vectors_substract(&base.pos, &tmp->pos, &l);
	dist = ft_norm2(&l);
	ft_normalize(&l);
	color->intensity += (ft_ombre(&base, dist, scene, tmp) *
	(ft_scal_produce(&l, &base.normal) +
	ft_specular(&base, &l, *(scene->camera)))
	/ dist) * tmp->i * 1000;
	if (color->intensity == 0)
	{
		ft_vectors_mult(&base.normal, -1, &base.normal);
		color->intensity += (ft_ombre(&base, dist, scene, tmp) *
	(ft_scal_produce(&l, &base.normal) +
	ft_specular(&base, &l, *(scene->camera)))
	/ dist) * tmp->i * 1000;
	}
	ft_calculate_color(color, scene, base, tmp);
}

void		ft_check_magic(t_list *obj, t_palette *color)
{
	if (obj->magic == 3)
		color->magic = 3;
	else
		color->magic = 0;
}
