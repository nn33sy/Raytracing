/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:22:16 by user42            #+#    #+#             */
/*   Updated: 2021/04/08 11:16:20 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_initialize_img(t_vars *vars, t_data *img, t_scene *scene)
{
	img->img = mlx_new_image(vars->mlx, scene->r_y, scene->r_x);
	img->addr = mlx_get_data_addr(img->img,
			&(img->bits_per_pixel), &(img->line_length), &(img->endian));
}

void	ft_initialize_window(t_vars *vars, t_scene *scene)
{
	int	rx;
	int	ry;

	vars->mlx = mlx_init();
	mlx_get_screen_size(vars->mlx, &rx, &ry);
	if (scene->r_x > rx)
		scene->r_x = rx;
	if (scene->r_y > ry)
		scene->r_y = ry;
	if (vars->photo == 0)
		vars->win = mlx_new_window(vars->mlx, scene->r_y,
				scene->r_x, "Hello Minirt!");
}
