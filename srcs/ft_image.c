#include "minirt.h"

int		key_hook(int keycode, t_vars *vars)
{
	if (keycode == 32)
		ft_export_bmp("hello", vars);
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

void	ft_put_color_pixel(t_palette *color)
{
	if (!(color->rgb.r == 0 && color->rgb.g == 0 && color->rgb.b == 0))
	{
		if (color->magic == 0)
		{
			color->rgb.r = (color->rgb.r / nrays);
			color->rgb.g = (color->rgb.g / nrays);
			color->rgb.b = (color->rgb.b / nrays);
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

void	ft_initialize_img(t_vars *vars, t_data *img, t_scene *scene)
{
	img->img = mlx_new_image(vars->mlx, scene->r_y, scene->r_x);
	img->addr = mlx_get_data_addr(img->img,
&(img->bits_per_pixel), &(img->line_length), &(img->endian));
}

void	ft_clean_rgb(t_palette *color_f)
{
	color_f->rgb.r = 0;
	color_f->rgb.g = 0;
	color_f->rgb.b = 0;
	color_f->intensity = 0;
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
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_key_hook(vars->win, key_hook, vars);
	mlx_loop(vars->mlx);
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
