#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mlx.h"
#include "function_maths.h"

typedef struct    s_vars
{
    void          *mlx;
    void          *win;
}                 t_vars;
typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

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
typedef struct s_scene
{
    t_light *light;
    t_ray   *ray;
    t_sphere *sphere;
    int     h;
    int     w;
    double  fov;

}t_scene;

void ft_parsing_scene(t_scene *scene)
{
    scene->h = 400;
    scene->fov = 60 *PI / 180;
    scene->w = 400;
    scene->light = malloc(sizeof(t_light));
    scene->light->pos=malloc(sizeof(t_coord));
    ft_coord(15,60, -40,scene->light->pos);
    scene->light->i = 1000000;

    scene->ray = malloc(sizeof(t_ray));
    scene->ray->origin = malloc(sizeof(t_coord));
    scene->ray->direction = malloc(sizeof(t_coord));
    ft_coord(0, 0,0, scene->ray->origin);
}

int             main(void)
{
    t_vars      vars;
    t_data  img;
    int     i= 0;
    int     j = 0;
    t_scene *scene = malloc(sizeof(t_scene));
    ft_parsing_scene(scene);

   t_sphere *sphere = malloc(sizeof(t_sphere));
    sphere->rayon = 20;
    sphere->origin = malloc(sizeof(t_coord));
    ft_coord(0,0, -55,sphere->origin);
    sphere->color= malloc(sizeof(t_coord));
    ft_coord(1,1,0,sphere->color);



    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, scene->h, scene->w, "Hello world!");
     img.img = mlx_new_image(vars.mlx, scene->h, scene->w);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);


t_coord *pos = malloc(sizeof(t_coord));
t_coord *normal = malloc(sizeof(t_coord));
t_coord *l =malloc(sizeof(t_coord));

while (i < scene->h)
{
    while (j < scene->w)
    {
        ft_coord(j-(scene->w/2),i-(scene->h/2), -scene->w/(2*tan(scene->fov/2)), scene->ray->direction);
        ft_normalize(scene->ray->direction);
        if (intersection_sphere(sphere,scene->ray,pos,normal) == 1)
            {
                double intensity;
                double dist;
                ft_vectors_substract(scene->light->pos,pos, l);
                dist = ft_norm2(l);
                ft_normalize(l);
                intensity = (scene->light->i * ft_max(ft_scal_produce(l,normal),255)) / dist ;
                if (intensity < 0)
                    intensity = 0;
                if (intensity > 255)
                    intensity = 255;
                my_mlx_pixel_put(&img, i, j,create_trgb(150,sphere->color->x * intensity,sphere->color->y * intensity,sphere->color->z * intensity));
            }
        j++;
    }
    j = 0;
    i++;
}
     mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
     mlx_loop(vars.mlx);
}