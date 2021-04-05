#include "minirt.h"

void	ft_put_color_pixel(t_palette *color)
{
	if (!(color->rgb.r == 0 && color->rgb.g == 0 && color->rgb.b == 0))
	{
		if (color->magic == 0)
		{
			color->rgb.r = (color->rgb.r / 1);
			color->rgb.g = (color->rgb.g / 1);
			color->rgb.b = (color->rgb.b / 1);
			ft_scale_rgb(&color->rgb);
		}
	}
}

void	ft_send_camera_rays(t_scene *scene
, int i, int j, t_camera *ptn)
{
	double x;
	double y;
	double z;

	ft_coord(i - (scene->r_y / 2), -j + (scene->r_x / 2)
	, -(scene->r_x / (2 * tan(ptn->fov / 2))), &ptn->ray.direction);
	x = (ptn->right.x * ptn->ray.direction.x)
	+ (ptn->right.y * ptn->ray.direction.y)
	+ (ptn->right.z * ptn->ray.direction.z);
	y = (ptn->up.x * ptn->ray.direction.x)
	+ (ptn->up.y * ptn->ray.direction.y) +
	(ptn->up.z * ptn->ray.direction.z);
	z = (ptn->forward.x * ptn->ray.direction.x)
	+ (ptn->forward.y * ptn->ray.direction.y)
	+ (ptn->forward.z * ptn->ray.direction.z);
	ft_coord(x, y, z, &ptn->ray.direction);
	ft_normalize(&ptn->ray.direction);
	ft_color_intensity(&scene->color_f, scene, &ptn->ray);
}

void	ft_create_image_2(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_hook(vars->win, 33, 0, ft_exit, vars);
	mlx_key_hook(vars->win, key_hook, vars);
	mlx_loop(vars->mlx);
}

void	ft_create_image(t_vars *vars, t_camera *cam, t_scene *scene)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	camera_matrice(cam);
	while (i < scene->r_y)
	{
		while (j < scene->r_x)
		{
			ft_send_camera_rays(scene, i, j, cam);
			ft_put_color_pixel(&scene->color_f);
			my_mlx_pixel_put(&vars->img, i, j
			, create_trgb(1, scene->color_f.rgb.r
			, scene->color_f.rgb.g, scene->color_f.rgb.b));
			ft_clean_rgb(&scene->color_f);
			scene->nb_rebond = 4;
			j++;
		}
		j = 0;
		i++;
	}
	ft_create_image_2(vars);
}

int		main_function(char *file_src)
{
	t_vars	vars;
	t_scene	*scene;

	scene = main_parsing(file_src);
	if (scene == NULL)
		exit(EXIT_FAILURE);
	scene->nb_rebond = 4;
	vars.scene = scene;
	scene->cam_actual = *(scene->camera);
	ft_initialize_window(&vars, scene);
	ft_initialize_img(&vars, &vars.img, scene);
	ft_create_image(&vars, scene->cam_actual, scene);
	return (1);
}
