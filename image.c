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

int ft_parsing_scene(t_scene *scene)
{
    scene->r_y = 600;
    scene->fov = 60 *PI / 180;
    scene->r_x = 600;
    scene->light = malloc(sizeof(t_light));
    ft_coord(-100,50, 150,&scene->light->pos);
    scene->light->i = 10000000;
    ft_coord(0, 0,0, &(scene->camera.origin));
    /*scene->amb->r = 20;
    scene->amb->g = 0;
    scene->amb->b = 20;
    scene->amb->ratio = 50;*/
    return(1);

}


int    ft_list_sphere(t_sphere **s)
{
    
    t_sphere *ptn;

    ptn = malloc(sizeof(t_sphere));

    ptn->rayon = 20;
    ft_coord(0,0, 150,&ptn->origin);
    ptn->mirror = 0;
    ptn->clear = 0;
   ptn->rgb.r= 70;
   ptn->rgb.g = 0;
   ptn->rgb.b = 3;
    ptn->next = NULL;
    
     ptn->next = malloc(sizeof(t_sphere));
    ptn->next->rayon = 10;
    ft_coord(0,-30, 130,&ptn->next->origin);
    ptn->next->rgb.r = 0.3;
    ptn->next->rgb.g = 50;
    ptn->next->rgb.b = 70;
    ptn->next->mirror = 0;
    ptn->next->next = NULL;
   
    ptn->next->next= malloc(sizeof(t_sphere));
    ptn->next->next->mirror = 0;
    ptn->next->next->rayon = 100;
    ptn->next->next->clear = 0;
    ft_coord(0,-150, 130,&ptn->next->next->origin);
    ptn->next->next->rgb.r = 60;
    ptn->next->next->rgb.g = 156;
    ptn->next->next->rgb.b = 0.1;

    ptn->next->next->next=NULL;

    *s = ptn;
    return(1);
}
void ft_initialize_img(t_vars *vars, t_data *img, t_scene *scene)
{
    vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, scene->r_y, scene->r_x, "Hello world!");
    img->img = mlx_new_image(vars->mlx, scene->r_y, scene->r_x);
    img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), &(img->line_length), &(img->endian));
}

float ft_ombre(t_sphere **list, t_sphere *sphere, t_coord *pos,t_coord *normal, double dist, t_scene *scene)
{
        t_ray ray_reflect;
        t_sphere *tmp;
        double t_inter;
       
        ft_vectors_substract(pos,&scene->light->pos, &ray_reflect.direction);
        ft_normalize(&ray_reflect.direction);
        tmp = *list;
        
        ft_vectors_mult(normal,0.001,&ray_reflect.origin);
        ft_vectors_add(&ray_reflect.origin,pos,&ray_reflect.origin);
                    while (tmp != NULL)
                    {  
                        if ((ft_visibilite(tmp, &ray_reflect, &t_inter) == 1 )) //  intersection
                                    if (t_inter *t_inter *t_inter < dist)
                                           return(0);
                            tmp = tmp->next;
                    }
        return(1);
}




double ft_color_intensity(t_palette *color, t_sphere **list, t_scene *scene, t_ray *ray, int *nb_rebond)
{
   
    double t_min = -1;
    t_sphere *sphere;
    sphere = *list;
    float V ;
double dist;
double intensity;

if (*nb_rebond == 0)
    return(0);
    
    t_coord *pos = malloc(sizeof(t_coord));
    t_coord *normal = malloc(sizeof(t_coord));
    t_coord *l =malloc(sizeof(t_coord));
    t_sphere *min;


       while (sphere != NULL)
            {
                 if (intersection_sphere(sphere,ray,pos,normal,&t_min) == 1 )
                     min = sphere;
                 sphere =sphere->next;
            }
            sphere = min;
            if (sphere != NULL)
{

                    ft_vectors_substract(pos,&scene->light->pos, l);
                    dist = ft_norm2(l);
                    ft_normalize(l);
                    V = ft_ombre(list, sphere, pos,normal, dist, scene);
                   
                    color->intensity = ((scene->light->i / PI)* ft_max(ft_scal_produce(l,normal),255) * V) / dist ;
                    color->intensity +=120;
                    color->intensity = (color->intensity < 0) ? 0 : color->intensity;
                    color->intensity = (color->intensity > 255) ? 255 : color->intensity;
                
                     color->rgb.r= sphere->rgb.r;
                    color->rgb.g= sphere->rgb.g;
                    color->rgb.b = sphere->rgb.b;
                return (color->intensity);
                }
                else
                    {
                        color->intensity = 1;
                        color->rgb.r= 0;
                    color->rgb.g= 0;
                    color->rgb.b = 0;
                        return (1);
                    }
}




int main_function(void)
{
    t_vars   vars;
   t_data  img;
    int     i= 0;
    int     j = 0;
    t_scene *scene = malloc(sizeof(t_scene));
    if (scene == 0 || ft_parsing_scene(scene) == -1)
    {
        free(scene);
        return(0);
    }
    t_sphere **list = malloc(sizeof(t_sphere *));
    if (list == 0 || ft_list_sphere(list) == -1)
        {
            free(list);
            return(0);
        }
    t_sphere *sphere = *list;

    ft_initialize_img(&vars, &img, scene);
    

t_ray *ray_reflect= malloc(sizeof(t_ray));

t_palette color;

int nb_rebond = 3;
int k;
t_palette color_f;
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
        ft_coord(i-(scene->r_y/2)+dx,-j+(scene->r_x/2)+dy, (scene->r_x/(2*tan(scene->fov/2))), &scene->camera.direction);
        ft_normalize(&scene->camera.direction);
        ft_color_intensity(&color, list,scene, &scene->camera, &nb_rebond);
        nb_rebond = 3;
        color_f.rgb.r += color.rgb.r;
        color_f.rgb.g += color.rgb.g;
        color_f.rgb.b += color.rgb.b;
        color_f.intensity += color.intensity;
        k++;

        }
        color_f.rgb.r /= nrays;
        color_f.rgb.g /= nrays;
        color_f.rgb.b /= nrays;
        color_f.intensity/= nrays;
        my_mlx_pixel_put(&img, i, j,create_trgb(150,sqrt(color_f.rgb.r * color_f.intensity),sqrt(color_f.rgb.g * color_f.intensity),sqrt(color_f.rgb.b * color_f.intensity)));
        color.rgb.r = 0;
        color.rgb.g = 0;
        color.intensity = 0;
        color.rgb.b = 0;
        color_f.rgb.r =0;
        color_f.rgb.g =0;
        color_f.rgb.b =0;
        color_f.intensity  =0;

        j++;
    }
  
         j = 0;
    i++;
    }
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
    mlx_loop(vars.mlx);
    return(1);
}
