#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "minilibx-linux/mlx.h"
#include "function_maths.h"
#include "get_next_line.h"
#include "libft.h"
#include "parsing.h"
#include "image.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}


void ft_initialize_img(t_vars *vars, t_data *img, t_scene *scene)
{
    vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, scene->r_y, scene->r_x, "Hello world!");
    img->img = mlx_new_image(vars->mlx, scene->r_y, scene->r_x);
    img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), &(img->line_length), &(img->endian));
}
