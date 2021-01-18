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




float ft_ombre(t_coord *pos,t_coord *normal, double dist, t_scene *scene)
{
        t_ray ray_reflect;
        t_list *ptn;
        double t_inter = -1;
       
        ft_vectors_substract(pos,&scene->light->pos, &ray_reflect.direction);
        ft_normalize(&ray_reflect.direction);
        ptn = *(scene->list);
        ft_vectors_mult(normal,0.001,&ray_reflect.origin);
        ft_vectors_add(&ray_reflect.origin,pos,&ray_reflect.origin);
                    while (ptn != NULL)
                    { 
                        if (ptn->type == 0 && (intersection_sphere((t_sphere *)ptn->object, &ray_reflect, NULL, NULL, &t_inter)== 0)) 
                            if (t_inter *t_inter < dist)
                                    return(0);
                        if (ptn->type == 1 && (intersection_plan((t_plan *)ptn->object,&ray_reflect,NULL,NULL,&t_inter) == 0))
                            if (t_inter *t_inter < dist)
                                    return(0);
                        if (ptn->type == 2 && (intersection_square((t_square *)ptn->object, &ray_reflect,NULL,NULL,&t_inter) == 0))
                            if (t_inter *t_inter < dist)
                                    return(0);
                        if (ptn->type == 3 && (ft_intersection_triangle((t_triangle *)ptn->object, &ray_reflect,NULL,NULL,&t_inter) == 0))
                            if (t_inter *t_inter < dist)
                                    return(0);
                        if (ptn->type == 4 && (ft_intersection_cylinder((t_cylinder *)ptn->object, &ray_reflect,NULL,NULL,&t_inter) == 0))
                            if (t_inter * t_inter < dist)
                                return(0);
                            ptn = ptn->next;
                    }
        return(1);
}

void ft_ray_reflect(t_coord *normal, t_coord *light, t_coord *reflect)
{
    double coeff;

    coeff = ft_scal_produce(normal, light) * 2;
    ft_vectors_mult(normal, coeff, reflect);
    ft_vectors_substract(light, reflect, reflect);
}

double ft_specular(t_coord *normal, t_coord *light, t_camera *cam, t_coord *pos)
{
    t_coord reflect;
    t_coord v;
    double specular;

ft_vectors_mult(light, -1, light);
   ft_ray_reflect(normal, light, &reflect);
    ft_vectors_substract(&cam->ray.origin, pos, &v);
    ft_normalize(&reflect);
    ft_normalize(&v);
    specular = ft_scal_produce(&v, &reflect);
    ft_vectors_mult(light, -1, light);
    if (specular > 0)
    {
        specular = 0.2*pow(specular, 10);
        return(specular);
    }
    else
        return(0);

}

double ft_color_intensity(t_palette *color, t_scene *scene, t_ray *ray, int *nb_rebond)
{
   
    double t_min = -1;
    float V ;
double dist;
double intensity;
double specular;
t_coord reflect;

t_list *tmp= *(scene->list);
if (*nb_rebond == 0)
    return(0);
    
    t_coord *pos = malloc(sizeof(t_coord));
    t_coord *normal = malloc(sizeof(t_coord));
    t_coord *l =malloc(sizeof(t_coord));
    t_list *min;


       while (tmp != NULL)
            {
                 if (tmp->type == 0 && intersection_sphere((t_sphere *)tmp->object ,ray,pos,normal,&t_min) == 1 )
                     min = tmp;
                 if (tmp->type == 1 && intersection_plan((t_plan *)tmp->object, ray,pos,normal,&t_min) == 1)
                    min = tmp;
                if (tmp->type == 2 && intersection_square((t_square *)tmp->object, ray,pos,normal,&t_min) == 1)
                    min = tmp;
                if (tmp->type == 3 && ft_intersection_triangle((t_triangle *)tmp->object, ray,pos,normal,&t_min) == 1)
                    min = tmp;
                if (tmp->type == 4 && ft_intersection_cylinder((t_cylinder*)tmp->object, ray,pos,normal,&t_min) == 1)
                    min = tmp;
                 tmp = tmp->next;
            }
            if (min != NULL)
{
                   
                    ft_vectors_substract(pos,&scene->light->pos, l);
                    dist = ft_norm2(l);
                    ft_normalize(l);
                    V = ft_ombre(pos,normal, dist, scene);

                   color->intensity = V * (ft_scal_produce(l,normal) / dist) * scene->light->i * 100000;
                  if (V == 1)
                  {
                   color->intensity += ft_specular(normal, l, &scene->camera, pos);
                    /*
                    ft_vectors_mult(&ray->direction, -1,&ray->direction);
                    ft_vectors_add(&ray->direction, l, &h);
                    ft_vectors_mult(&h, -1,&h);
                    ft_normalize(&h);
                    ft_vectors_mult(&ray->direction, -1,&ray->direction);
                    if (ft_scal_produce(normal,&h) > 0)
                    {
                        specular = 500 * scene->light->i * pow(ft_scal_produce(normal,&h),10);
                        printf("hey");

                    }
            
                    else
                        specular = 0;
                    //printf(" %f ",specular);*/
                   // color->intensity += specular;
                  }
                    if (min->type == 0)
                    {
                    color->rgb.r= ((t_sphere*)(min->object))->rgb.r;
                    color->rgb.g=  ((t_sphere*)(min->object))->rgb.g;
                    color->rgb.b =((t_sphere*)(min->object))->rgb.b;
                    }
                    if (min->type == 1)
                    {
                    color->rgb.r= ((t_plan*)(min->object))->rgb.r;
                    color->rgb.g=  ((t_plan*)(min->object))->rgb.g;
                    color->rgb.b =((t_plan*)(min->object))->rgb.b;
                    }
                    if (min->type == 2)
                    {
                    color->rgb.r= ((t_square*)(min->object))->rgb.r;
                    color->rgb.g=  ((t_square*)(min->object))->rgb.g;
                    color->rgb.b =((t_square*)(min->object))->rgb.b;
                    }
                    if (min->type == 3)
                    {
                    color->rgb.r= ((t_triangle*)(min->object))->rgb.r;
                    color->rgb.g=  ((t_triangle*)(min->object))->rgb.g;
                    color->rgb.b =((t_triangle*)(min->object))->rgb.b;
                    }
                    if (min->type == 4)
                    {
                    color->rgb.r= ((t_cylinder*)(min->object))->rgb.r;
                    color->rgb.g=  ((t_cylinder*)(min->object))->rgb.g;
                    color->rgb.b =((t_cylinder*)(min->object))->rgb.b;
                    }
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

void ft_scale_rgb(t_rgb *rgb)
{
    ft_scaling_one_value(&rgb->g);
    ft_scaling_one_value(&rgb->r);
    ft_scaling_one_value(&rgb->b);
}
void ft_scaling_one_value(double *value)
{
    if (*value > 255)
        *value = 255;
    if (*value < 0)
        *value = 0;
}
void ft_calculate_angle(t_coord *u, t_coord *v, t_coord *angle)
{
    double tmp_u;
    double tmp_v;
    double res;

    tmp_u = u->x;
    tmp_v = v->x;
    u->x = 0;
    v->x = 0;
    res = -ft_scal_produce(u,v);
    printf("h%fh,",res);
    res /= (sqrt(ft_norm2(u)) * sqrt(ft_norm2(v)));
    angle->x = acos(res);
    u->x = tmp_u;
    v->x = tmp_v;

    printf("?%f?|%f| ",res,angle->x *(180/3.14));

    tmp_u = u->y;
    tmp_v = v->y;
    u->y = 0;
    v->y = 0;
    res = ft_scal_produce(u,v);
    res /= (sqrt(ft_norm2(u)) * sqrt(ft_norm2(v)));
    angle->y = acos(res);
    u->y = tmp_u;
    v->y = tmp_v;

    printf("|%f| ",angle->y *(3.14/180));

    tmp_u = u->z;
    tmp_v = v->z;
    u->z = 0;
    v->z = 0;
    res = ft_scal_produce(u,v);
    res /= (sqrt(ft_norm2(u)) * sqrt(ft_norm2(v)));
    angle->z = acos(res);
    u->z = tmp_u;
    v->z = tmp_v;
    printf("|%f| ",angle->z *(3.14/180));
}

void camera_matrice(t_scene *scene)
{
    t_coord tmp;

    ft_normalize( &scene->camera.forward);
    ft_coord(-scene->camera.direction.x, -scene->camera.direction.y, -scene->camera.direction.z, &scene->camera.forward);
    if (scene->camera.direction.x == 0 && scene->camera.direction.z == 0 && (scene->camera.direction.y == 1 || scene->camera.direction.y == -1))
            ft_coord(1, 0, 0, &scene->camera.right);
    else
    {
        ft_coord(0, 1, 0, &tmp);
        ft_produit_vectoriel(&tmp, &scene->camera.forward, &scene->camera.right);
    }
    ft_produit_vectoriel(&scene->camera.forward, &scene->camera.right, &scene->camera.up);
}

int main_function(void)
{
    t_vars   vars;
   t_data  img;
    int     i= 0;
    int     j = 0;
    t_coord angle;
    t_scene *scene = main_parsing();

ft_initialize_img(&vars, &img, scene);
t_ray *ray_reflect= malloc(sizeof(t_ray));

t_palette color;

int nb_rebond = 3;
int k;
double x;
double y;
double z;
camera_matrice(scene);
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

ft_coord(i-(scene->r_y/2)+dx,-j+(scene->r_x/2)+dy,-(scene->r_x/(2*tan(scene->fov/2))), &scene->camera.ray.direction);
x = (scene->camera.right.x * scene->camera.ray.direction.x) + (scene->camera.right.y * scene->camera.ray.direction.y) + (scene->camera.right.z * scene->camera.ray.direction.z);
y = (scene->camera.up.x * scene->camera.ray.direction.x) + (scene->camera.up.y * scene->camera.ray.direction.y) + (scene->camera.up.z * scene->camera.ray.direction.z);
z =  (scene->camera.forward.x * scene->camera.ray.direction.x) + (scene->camera.forward.y * scene->camera.ray.direction.y) + (scene->camera.forward.z * scene->camera.ray.direction.z);
ft_coord(x,y,z, &scene->camera.ray.direction);
        ft_normalize(&scene->camera.ray.direction);
        ft_color_intensity(&color,scene, &scene->camera.ray, &nb_rebond);
        nb_rebond = 3;
        color_f.rgb.r += color.rgb.r;
        color_f.rgb.g += color.rgb.g;
        color_f.rgb.b += color.rgb.b;
        color_f.intensity += color.intensity;
        k++;

        }
        color_f.rgb.r = (color_f.rgb.r / nrays) + scene->light->rgb.r;
        color_f.rgb.g = (color_f.rgb.g / nrays) + scene->light->rgb.g;
        color_f.rgb.b = (color_f.rgb.b / nrays) + scene->light->rgb.b;
        color_f.intensity/= nrays;
      //  color_f.intensity += scene->amb_light.ratio * 0.3;
        color_f.rgb.r = (color_f.rgb.r *color_f.intensity) + (scene->amb_light.ratio * scene->amb_light.rgb.r * 0.1);
        color_f.rgb.g = (color_f.rgb.g *color_f.intensity) + (scene->amb_light.ratio * scene->amb_light.rgb.g * 0.1);
        color_f.rgb.b = (color_f.rgb.b *color_f.intensity) + (scene->amb_light.ratio * scene->amb_light.rgb.b * 0.1);
        ft_scale_rgb(&color_f.rgb);
        my_mlx_pixel_put(&img, i, j,create_trgb(1,color_f.rgb.r,color_f.rgb.g,color_f.rgb.b));
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
        printf("OK");
    }
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
    mlx_loop(vars.mlx);
    return(1);
}
