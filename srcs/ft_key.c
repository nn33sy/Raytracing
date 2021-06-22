/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:52:42 by how-choon         #+#    #+#             */
/*   Updated: 2021/04/09 14:26:21 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 32)
		ft_export_bmp("photoo", vars);
	if (keycode == 65307)
	{
		ft_clean(vars);
		exit(EXIT_FAILURE);
	}
	if (keycode == 65363 && vars->scene->cam_actual->next != NULL)
	{
		vars->scene->cam_actual = vars->scene->cam_actual->next;
		ft_create_image(vars, vars->scene->cam_actual, vars->scene);
	}
	if (keycode == 65361 && vars->scene->cam_actual->before != NULL)
	{
		vars->scene->cam_actual = vars->scene->cam_actual->before;
		ft_create_image(vars, vars->scene->cam_actual, vars->scene);
	}
	return (0);
}

int	ft_imagewin(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int	ft_exit(t_vars *vars)
{
	ft_clean(vars);
	exit(EXIT_FAILURE);
}
