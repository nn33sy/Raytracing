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


int             key_hook(int keycode, t_vars *vars)
{
    if (keycode == 65307)
    {

         exit(EXIT_FAILURE);
    }
    if (keycode == 65363 && vars->scene->cam_actual->next != NULL)
    {
        vars->scene->cam_actual = vars->scene->cam_actual->next;
        ft_create_image(vars, vars->scene->cam_actual ,vars->scene);
    }
    if (keycode == 65361 && vars->scene->cam_actual->before != NULL)
    {
        vars->scene->cam_actual = vars->scene->cam_actual->before;
        ft_create_image(vars, vars->scene->cam_actual ,vars->scene);

    }
}
void ft_put_color_pixel(t_palette *color, t_scene *scene)
{
        if (!(color->rgb.r == 0 && color->rgb.g == 0 && color->rgb.b == 0))
        {
        if (color->magic == 0)
        {
        color->rgb.r = (color->rgb.r / nrays) ;
        color->rgb.g = (color->rgb.g / nrays) ;
        color->rgb.b = (color->rgb.b / nrays) ;
        ft_scale_rgb(&color->rgb);
        }
        }

}


void ft_send_camera_rays(t_scene *scene, int i, int j, t_palette *color_f, t_camera *ptn)
{
    double x;
    double y;
    double z;

    ft_coord(i-(scene->r_y/2),-j+(scene->r_x/2),-(scene->r_x/(2*tan(ptn->fov/2))), &ptn->ray.direction);
    x = (ptn->right.x * ptn->ray.direction.x) + (ptn->right.y * ptn->ray.direction.y) + (ptn->right.z * ptn->ray.direction.z);
    y = (ptn->up.x * ptn->ray.direction.x) + (ptn->up.y * ptn->ray.direction.y) + (ptn->up.z * ptn->ray.direction.z);
    z =  (ptn->forward.x * ptn->ray.direction.x) + (ptn->forward.y * ptn->ray.direction.y) + (ptn->forward.z * ptn->ray.direction.z);
    ft_coord(x,y,z, &ptn->ray.direction);
    ft_normalize(&ptn->ray.direction);
     ft_color_intensity(color_f,scene, &ptn->ray); 

}

void	ft_initialize_img(t_vars *vars, t_data *img, t_scene *scene)
{

	img->img = mlx_new_image(vars->mlx, scene->r_y, scene->r_x);
	img->addr = mlx_get_data_addr(img->img,
&(img->bits_per_pixel), &(img->line_length), &(img->endian));
}

void ft_create_image(t_vars *vars, t_camera *cam, t_scene *scene)
{
        int     i= 0;
    int     j = 0;
    int nb_rebond = 4;
    t_palette color_f;
    double k;

    camera_matrice(cam);
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
            ft_send_camera_rays(scene, i, j, &color_f, cam);
        k++;
        }
        ft_put_color_pixel(&color_f, scene);
        my_mlx_pixel_put(&vars->img, i, j,create_trgb(1,color_f.rgb.r,color_f.rgb.g,color_f.rgb.b));
       
        color_f.rgb.r =0;
        color_f.rgb.g =0;
        color_f.rgb.b =0;
        scene->nb_rebond = 4;
        color_f.intensity  = 0;
        j++;

    }
         j = 0;
        i++;
     
    }
    char *chain;
    chain = ft_strdup("hello");
    ft_export_bmp(chain, vars);
    mlx_clear_window(vars->mlx, vars->win);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
    mlx_key_hook(vars->win, key_hook, vars);
   mlx_loop(vars->mlx);

}

int main_function(char *file_src)
{
    t_vars   vars;
   t_data  *img;
   

    t_scene *scene = main_parsing(file_src);

scene->nb_rebond = 4;
vars.scene= scene;

scene->cam_actual = *(scene->camera);

ft_initialize_window(&vars, scene);
ft_initialize_img(&vars, &vars.img, scene);
ft_create_image(&vars, scene->cam_actual, scene);



    return(1);
}
