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

int	ft_exit(t_vars *vars)
{
	ft_clean(vars);
	exit(EXIT_FAILURE);
}
