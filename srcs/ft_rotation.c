/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 13:32:29 by user42            #+#    #+#             */
/*   Updated: 2021/04/07 19:03:31 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		rx(t_coord *vect, double x)
{
	t_coord	tmp;

	tmp.x = vect->x;
	tmp.y = vect->y;
	tmp.z = vect->z;
	vect->y = tmp.y * cos(x) - tmp.z * sin(x);
	vect->z = tmp.y * sin(x) + tmp.z * cos(x);
}

void		ry(t_coord *vect, double y)
{
	t_coord	tmp;

	tmp.x = vect->x;
	tmp.y = vect->y;
	tmp.z = vect->z;
	vect->x = tmp.x * cos(y) + tmp.z * sin(y);
	vect->z = tmp.x * -sin(y) + tmp.z * cos(y);
}

void		rz(t_coord *vect, double z)
{
	t_coord	tmp;

	tmp.x = vect->x;
	tmp.y = vect->y;
	tmp.z = vect->z;
	vect->x = tmp.x * cos(z) - tmp.y * sin(z);
	vect->y = tmp.x * sin(z) + tmp.y * cos(z);
}

void		rot(t_coord *vect, t_coord *angle)
{
	rx(vect, angle->x);
	ry(vect, angle->y);
	rz(vect, angle->z);
}

void		anti_rot(t_coord *vect, t_coord *angle)
{
	rz(vect, -angle->z);
	ry(vect, -angle->y);
	rx(vect, -angle->x);
}
