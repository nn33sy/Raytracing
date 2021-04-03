/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_maths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <how-choongines@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:16:00 by user42            #+#    #+#             */
/*   Updated: 2021/04/03 19:24:46 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_coord(double x, double y, double z, t_coord *pt)
{
	pt->x = x;
	pt->y = y;
	pt->z = z;
}

void	ft_vect(t_coord *a, t_coord *b, t_coord *ab)
{
	ab->x = b->x - a->x;
	ab->y = b->y - a->y;
	ab->z = b->z - a->z;
}

void	ft_produit_vectoriel(t_coord *a, t_coord *b, t_coord *prod)
{
	prod->x = (a->y * b->z) - (a->z * b->y);
	prod->y = (a->z * b->x) - (a->x * b->z);
	prod->z = (a->x * b->y) - (a->y * b->x);
}

void	ft_vectors_substract(t_coord *a, t_coord *b, t_coord *res)
{
	res->x = b->x - a->x;
	res->y = b->y - a->y;
	res->z = b->z - a->z;
}

void	ft_vectors_add(t_coord *a, t_coord *b, t_coord *res)
{
	res->x = a->x + b->x;
	res->y = a->y + b->y;
	res->z = a->z + b->z;
}
