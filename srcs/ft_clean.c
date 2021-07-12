/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:02:27 by how-choongi       #+#    #+#             */
/*   Updated: 2021/04/07 19:02:28 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_free_camera(t_camera *cam)
{
	if (cam->next != NULL)
		ft_free_camera(cam->next);
	free(cam);
}

void	ft_free_light(t_light *light)
{
	if (light->next != NULL)
		ft_free_light(light->next);
	free(light);
}

void	ft_free_list(t_list *list)
{
	if (list->next != NULL)
		ft_free_list(list->next);
	if (list->object != NULL)
		free(list->object);
	free(list);
}

void	ft_clean_scene(t_scene *scene)
{
	if (scene->camera != NULL)
	{
		if (*(scene->camera) != NULL)
			ft_free_camera(*(scene->camera));
		free(scene->camera);
	}
	if (scene->light != NULL)
	{
		if (*(scene->light) != NULL)
			ft_free_light(*(scene->light));
		free(scene->light);
	}
	if (scene->list != NULL)
	{
		if (*(scene->list) != NULL)
			ft_free_list(*(scene->list));
		free(scene->list);
	}
}

void	ft_clean(t_vars *vars)
{
	if (vars->scene != NULL)
	{
		ft_clean_scene(vars->scene);
		free(vars->scene);
	}
	if (vars->img.img != NULL)
		mlx_destroy_image(vars->mlx, vars->img.img);
	/*if (vars->mlx != NULL)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}*/
	if (vars->win != NULL)
	{
		mlx_destroy_window(vars->mlx, vars->win);
	//	free(vars->win);
	}
	if(vars->mlx != NULL)
	{	
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
}
