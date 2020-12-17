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
    scene->h = 600;
    scene->fov = 60 *PI / 180;
    scene->w = 600;
    scene->light = malloc(sizeof(t_light));
    if (scene->light == 0)
        return(-1);
    scene->light->pos=malloc(sizeof(t_coord));
    if (scene->light->pos == 0)
    {
        free(scene->light);
        return(-1);
    }
    scene->ray = malloc(sizeof(t_ray));
    if (scene->ray == 0)
    {
        free(scene->light->pos);
        free(scene->light);
        return(-1);
    }
    scene->ray->origin = malloc(sizeof(t_coord));
    if (scene->ray->origin == 0)
    {
        free(scene->light->pos);
        free(scene->light);
        free(scene->ray);
        return(-1);
    }
    scene->ray->direction = malloc(sizeof(t_coord));
    if (scene->ray->direction == 0)
    {
        free(scene->light->pos);
        free(scene->light);
        free(scene->ray->origin);
        free(scene->ray);
        return(-1);
    }
    ft_coord(15,70, 30,scene->light->pos);
    scene->light->i = 100000000;
    ft_coord(0, 0,0, scene->ray->origin);
    return(1);
}
int    ft_list_sphere(t_sphere **s)
{
    
    t_sphere *ptn;
    ptn = malloc(sizeof(t_sphere));
    if (ptn == 0)
        return(-1);
/*
        ptn->rayon = 250;
    ptn->origin = malloc(sizeof(t_coord));
    ft_coord(0,290, 300,ptn->origin);
    ptn->color= malloc(sizeof(t_coord));
    ft_coord(0,2,0,ptn->color);
    ptn->next = NULL;
    */
    ptn->rayon = 5;
    ptn->origin = malloc(sizeof(t_coord));
    if (ptn->origin == 0)
    {
        free(ptn);
        return(-1);
    }
    ft_coord(0,10, 55,ptn->origin);
    ptn->mirror = 0;
    ptn->clear = 1;
    ptn->color= malloc(sizeof(t_coord));
    if (ptn->color == 0)
    {
        free(ptn->origin);
        free(ptn);
        return(-1);
    }
    
    ft_coord(1,1,0,ptn->color);
    /*
     ptn->next = malloc(sizeof(t_sphere));
    ptn->next->rayon = 250;
    ptn->next->origin = malloc(sizeof(t_coord));
    ft_coord(0,290, 200,ptn->next->origin);
    ptn->next->color= malloc(sizeof(t_coord));
    ft_coord(0,2,0,ptn->next->color);
    ptn->next->mirror = 0;
    ptn->next->next = NULL;
*/
/*
    ptn->next = malloc(sizeof(t_sphere));
    ptn->next->rayon = 35;
    ptn->next->origin = malloc(sizeof(t_coord));
    ft_coord(30,0, 200,ptn->next->origin);
    ptn->next->color= malloc(sizeof(t_coord));
    ft_coord(1,0,1,ptn->next->color);
    
    ptn->next->mirror =0;*/

    ptn->next = malloc(sizeof(t_sphere));
    ptn->next->mirror = 0;
    ptn->next->rayon = 2000;
    ptn->next->clear = 0;
    ptn->next->origin = malloc(sizeof(t_coord));
    ft_coord(0,-2000-20, 0,ptn->next->origin);
    ptn->next->color= malloc(sizeof(t_coord));
    ft_coord(0,2,3,ptn->next->color);

    ptn->next->next= malloc(sizeof(t_sphere));
    ptn->next->next->mirror = 0;
    ptn->next->next->rayon = 2000;
    ptn->next->next->clear = 0;
    ptn->next->next->origin = malloc(sizeof(t_coord));
    ft_coord(0,0, 3500,ptn->next->next->origin);
    ptn->next->next->color= malloc(sizeof(t_coord));
    ft_coord(1,0,2,ptn->next->next->color);
    ptn->next->next->next=NULL;
    
    ptn->next->next->next = malloc(sizeof(t_sphere));
    ptn->next->next->next->mirror = 0;
    ptn->next->next->next->clear = 1;
    ptn->next->next->next->rayon = 10;
    ptn->next->next->next->origin=malloc(sizeof(t_coord));
    ft_coord(10,0,80,ptn->next->next->next->origin);
        ptn->next->next->next->color= malloc(sizeof(t_coord));
    ft_coord(0,1,0,ptn->next->next->next->color);
    ptn->next->next->next->next = NULL;


        ptn->next->next->next->next = malloc(sizeof(t_sphere));
    ptn->next->next->next->next->mirror = 0;
    ptn->next->next->next->next->clear = 0;
    ptn->next->next->next->next->rayon = 2000;
    ptn->next->next->next->next->origin=malloc(sizeof(t_coord));
    ft_coord(-2200,0,0,ptn->next->next->next->next->origin);
        ptn->next->next->next->next->color= malloc(sizeof(t_coord));
    ft_coord(1,1,2,ptn->next->next->next->next->color);
    ptn->next->next->next->next->next =NULL;
    *s = ptn;
    return(1);
}
void ft_initialize_img(t_vars *vars, t_data *img, t_scene *scene)
{
    vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, scene->h, scene->w, "Hello world!");
    img->img = mlx_new_image(vars->mlx, scene->h, scene->w);
    img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), &(img->line_length), &(img->endian));
}

int ft_ombre(t_sphere **list, t_sphere *sphere, t_coord *pos, double dist, t_scene *scene)
{
        t_ray ray_reflect;
        t_sphere *tmp;
        double t_inter;

        ray_reflect.direction = malloc(sizeof(t_coord));
        ray_reflect.origin = pos;
        ft_vectors_substract(scene->light->pos,pos, ray_reflect.direction);
        ft_normalize(ray_reflect.direction);
        tmp = *list;
                    while (tmp != NULL)
                    {  
                        if ((tmp != sphere) && (ft_visibilite(tmp, &ray_reflect, &t_inter) == 1 )) //  intersection
                                {
                                    if (t_inter * t_inter < dist)
                                        return(0);
                                }
                            tmp = tmp->next;
                    }
        free(ray_reflect.direction);
        return(1);
}

typedef struct s_palette{
    double r;
    double g;
    double b;
    double intensity;
}t_palette;


void ft_color_intensity(t_palette *color, t_sphere **list, t_scene *scene, t_ray *ray, int *nb_rebond)
{
    double t_min = -1;
    t_sphere *sphere;
    sphere = *list;
    int V ;
double dist;
    double n1;
    double n2;

if (*nb_rebond == 0)
{
     color->r = 0;
    color->g = 0;
    color->b = 0;
    return;
}

    t_coord *pos = malloc(sizeof(t_coord));
    t_coord *normal = malloc(sizeof(t_coord));
    t_coord *l =malloc(sizeof(t_coord));

    t_ray mirror;
    t_ray refract_glass;
    refract_glass.direction =malloc(sizeof(t_coord));
    refract_glass.origin=malloc(sizeof(t_coord));
       while (sphere != NULL)
            {
                if (intersection_sphere(sphere,ray,pos,normal,&t_min) == 1)
                { 
                    if (sphere->mirror == 1)
                    {
                        t_coord res;

                        mirror.origin  = malloc(sizeof(t_coord));
                         ft_vectors_mult(normal,0.001, mirror.origin);
                         ft_vectors_add(mirror.origin,pos,mirror.origin);
                     
                        

                          mirror.direction  = malloc(sizeof(t_coord));
                        ft_vectors_mult(normal,2 * ft_scal_produce(ray->direction,normal),&res);
                        ft_vectors_substract(&res,ray->direction,mirror.direction); 
                        *nb_rebond -= 1;
                        ft_color_intensity(color,list, scene,&mirror, nb_rebond);
                        
                    }
                    else 
                        if (sphere->clear == 1)
                    {

                        if (ft_scal_produce(ray->direction, normal) > 0)
                        {// Sort de la sphere 
                            n1 = GLASS;
                            n2 = AIR;
                        }
                        else
                        {//Rrentre dans la sphere
                            n1 = AIR;
                            n2 = GLASS;
                            ft_vectors_mult(normal, -1,normal);
                        }
                        ft_vectors_mult(normal,0.001,refract_glass.origin);
                        ft_vectors_substract(refract_glass.origin,pos,refract_glass.origin);
                        t_coord tn;
                        ft_vectors_mult(normal, ft_scal_produce(ray->direction,normal),&tn);
                        ft_vectors_substract(&tn,ray->direction,&tn);
                        ft_vectors_mult(&tn, n1/n2,&tn);
                        t_coord t_t;
                        double delta;
                        delta = 1-(pow((n1/n2),2)*pow((1-ft_scal_produce(ray->direction,normal)),2));
                        if (delta < 0)
                        {
                                 color->r = 0;
                                color->g = 0;
                                color->b = 0;
                                color->intensity = 0;
                                return;
                        }
                        ft_vectors_mult(normal,-sqrt(delta),&t_t);
                        ft_vectors_add(&t_t,&tn,refract_glass.direction)  ;

                        *nb_rebond -= 1;
                        ft_color_intensity(color,list, scene,&refract_glass, nb_rebond);

                    }
                    else
                    {
                    ft_vectors_substract(pos,scene->light->pos, l);
                    dist = ft_norm2(l);
                    ft_normalize(l);
                    V = ft_ombre(list, sphere, pos, dist, scene);
                    color->intensity = (scene->light->i * ft_max(ft_scal_produce(l,normal),255) * V) / dist ;
                    color->intensity = (color->intensity < 0) ? 0 : color->intensity;
                    color->intensity = (color->intensity > 255) ? 255 : color->intensity;
                    color->r = sphere->color->x;
                    color->g = sphere->color->y;
                    color->b = sphere->color->z;
                    }
                    }
                  sphere = sphere->next;
            }
        free(pos);
        free(normal);
        free(l);
}


int             main(void)
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
ray_reflect->direction = malloc(sizeof(t_coord));

t_palette color;
int nb_rebond = 5;
while (i < scene->h)
{
    while (j < scene->w)
    {
        ft_coord(i-(scene->h/2),-j+(scene->w/2), (scene->h/(2*tan(scene->fov/2))), scene->ray->direction);
        ft_normalize(scene->ray->direction);
        ft_color_intensity(&color, list,scene, scene->ray, &nb_rebond);
        my_mlx_pixel_put(&img, i, j,create_trgb(150,color.r * color.intensity,color.g * color.intensity,color.b * color.intensity));
        color.r = 0;
        color.g = 0;
        color.b = 0;
        j++;
        nb_rebond = 5;
    }
    j = 0;
    i++;
}
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
    mlx_loop(vars.mlx);
}