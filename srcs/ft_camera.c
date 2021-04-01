/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 23:20:03 by how-choongi       #+#    #+#             */
/*   Updated: 2021/04/01 16:39:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	camera_matrice(t_camera *cam)
{
	t_coord	tmp;

	ft_normalize(&cam->forward);
	ft_coord(-cam->direction.x, -cam->direction.y,
-cam->direction.z, &cam->forward);
	if (cam->direction.x == 0 && cam->direction.z == 0 &&
(cam->direction.y == 1 || cam->direction.y == -1))
		ft_coord(1, 0, 0, &cam->right);
	else
	{
		ft_coord(0, 1, 0, &tmp);
		ft_produit_vectoriel(&tmp, &cam->forward,
&cam->right);
	}
	ft_produit_vectoriel(&cam->forward, &cam->right
, &cam->up);
}
