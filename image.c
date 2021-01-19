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


void ft_put_color_pixel(t_palette *color, t_scene *scene)
{
        if (!(color->rgb.r == 0 && color->rgb.g == 0 && color->rgb.b == 0))
        {
        color->rgb.r = (color->rgb.r / nrays) ;
        color->rgb.g = (color->rgb.g / nrays) ;
        color->rgb.b = (color->rgb.b / nrays) ;
        ft_scale_rgb(&color->rgb);
        }

}

void ft_send_camera_rays(t_scene *scene, int i, int j, t_palette *color_f)
{
    int nb_rebond;
    double x;
    double y;
    double z;

    nb_rebond = 3;
    ft_coord(i-(scene->r_y/2),-j+(scene->r_x/2),-(scene->r_x/(2*tan(scene->fov/2))), &scene->camera.ray.direction);
    x = (scene->camera.right.x * scene->camera.ray.direction.x) + (scene->camera.right.y * scene->camera.ray.direction.y) + (scene->camera.right.z * scene->camera.ray.direction.z);
    y = (scene->camera.up.x * scene->camera.ray.direction.x) + (scene->camera.up.y * scene->camera.ray.direction.y) + (scene->camera.up.z * scene->camera.ray.direction.z);
    z =  (scene->camera.forward.x * scene->camera.ray.direction.x) + (scene->camera.forward.y * scene->camera.ray.direction.y) + (scene->camera.forward.z * scene->camera.ray.direction.z);
    ft_coord(x,y,z, &scene->camera.ray.direction);
    ft_normalize(&scene->camera.ray.direction);
     ft_color_intensity(color_f,scene, &scene->camera.ray, &nb_rebond); 

}

int main_function(void)
{
    t_vars   vars;
   t_data  img;
   t_palette color_f;
    int     i= 0;
    int     j = 0;
    t_scene *scene = main_parsing();
ft_initialize_img(&vars, &img, scene);
t_ray *ray_reflect= malloc(sizeof(t_ray));

int nb_rebond = 3;
int k;
double x;
double y;
double z;

while (i < scene->r_y)
{
    while (j < scene->r_x)
    {

       k = 0;
         double r1 = 0.5;
            double r2 = 0.5;
        while (k < nrays)
        {
            r1 +=0.05;
            r2-= 0.05;
            double R = sqrt(-2 *log(r1));
            double dx = R*cos(2 * PI *log(r2));
            double dy = R*sin(2 * PI*log(r2));
            if (nrays ==1)
            {
                dx = 0;
                dy=0;
            }
            ft_send_camera_rays(scene, i, j, &color_f);
        k++;
        }
        ft_put_color_pixel(&color_f, scene);
        my_mlx_pixel_put(&img, i, j,create_trgb(1,color_f.rgb.r,color_f.rgb.g,color_f.rgb.b));
        color_f.rgb.r =0;
        color_f.rgb.g =0;
        color_f.rgb.b =0;
        color_f.intensity  = 0;
        j++;
    }
  printf("ok");
         j = 0;
        i++;
    }
    printf("OK");
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
    mlx_loop(vars.mlx);
    return(1);
}
