#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mlx.h"
#include "function_maths.h"
#include "get_next_line.h"
#include "libft.h"
#include "parsing.h"


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


void ft_initialize_img(t_vars *vars, t_data *img, t_scene *scene)
{
    vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, scene->r_y, scene->r_x, "Hello world!");
    img->img = mlx_new_image(vars->mlx, scene->r_y, scene->r_x);
    img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), &(img->line_length), &(img->endian));
}

float ft_ombre(t_list **list, t_sphere *sphere, t_coord *pos,t_coord *normal, double dist, t_scene *scene)
{
        t_ray ray_reflect;
        t_list *ptn;
        double t_inter;
       
        ft_vectors_substract(pos,&scene->light->pos, &ray_reflect.direction);
        ft_normalize(&ray_reflect.direction);
        ptn = *list;
        
        ft_vectors_mult(normal,0.001,&ray_reflect.origin);
        ft_vectors_add(&ray_reflect.origin,pos,&ray_reflect.origin);
                    while (ptn != NULL)
                    {  
                        if (ptn->type == 0 && (ft_visibilite((t_sphere *)ptn->object, &ray_reflect, &t_inter) == 1 )) //  intersection
                                    if (t_inter *t_inter < dist)
                                           return(0);
                            ptn = ptn->next;
                    }
        return(1);
}




double ft_color_intensity(t_palette *color, t_scene *scene, t_ray *ray, int *nb_rebond)
{
   
    double t_min = -1;
    float V ;
double dist;
double intensity;

t_list *tmp= *(scene->list);


if (*nb_rebond == 0)
    return(0);
    
    t_coord *pos = malloc(sizeof(t_coord));
    t_coord *normal = malloc(sizeof(t_coord));
    t_coord *l =malloc(sizeof(t_coord));
    t_sphere *min;


       while (tmp != NULL)
            {
                 if (tmp->type == 0 && intersection_sphere((t_sphere *)tmp->object ,ray,pos,normal,&t_min) == 1 )
                     min = (t_sphere *)tmp->object;
                 /*if (tmp->type == 1 && interaction_plan((t_plan *)tmp->object, ray,pos,normal,&t_min) == 1)
                    min = (t_plan *)tmp->object;*/
                 tmp = tmp->next;
            }
            if (min != NULL)
{

                    ft_vectors_substract(pos,&scene->light->pos, l);
                    dist = ft_norm2(l);
                    ft_normalize(l);
                    V = ft_ombre(scene->list, min, pos,normal, dist, scene);
                    color->intensity = ((scene->light->i / PI)* ft_max(ft_scal_produce(l,normal),255) * V) / dist ;
                   ft_scaling_one_value(&(color->intensity));
                    color->intensity +=120;
                     color->rgb.r= min->rgb.r;
                    color->rgb.g=  min->rgb.g;
                    color->rgb.b = min->rgb.b;
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

void ft_scaling_one_value(double *value)
{
    if (*value > 255)
        *value = 255;
    if (*value < 0)
        *value = 0;
}


int main_function(void)
{
    t_vars   vars;
   t_data  img;
    int     i= 0;
    int     j = 0;
    t_scene *scene = main_parsing();

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
        ft_color_intensity(&color,scene, &scene->camera, &nb_rebond);
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
