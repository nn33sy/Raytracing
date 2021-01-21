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

t_list *ft_color_intensity_2(t_scene *scene, t_ray *ray, t_point *base)
{
    t_list *tmp; 
    double t_min;
    t_list *min;

    tmp = *(scene->list);
    min = NULL;
    t_min = -1;
           while (tmp != NULL)
            {
                
                 if (tmp->type == 0 && intersection_sphere((t_sphere *)tmp->object ,ray,base ,&t_min) == 1 )
                     min = tmp;
                 if (tmp->type == 1 && intersection_plan((t_plan *)tmp->object, ray, base,&t_min) == 1)
                    min = tmp;
                if (tmp->type == 2 && intersection_square((t_square *)tmp->object, ray,base,&t_min) == 1)
                    min = tmp;
                if (tmp->type == 3 && ft_intersection_triangle((t_triangle *)tmp->object, ray,base ,&t_min) == 1)
                    min = tmp;
                if (tmp->type == 4 && ft_intersection_cylinder((t_cylinder*)tmp->object, ray,base ,&t_min) == 1)
                    min = tmp;
                 tmp = tmp->next;
            }
    return(min);
}

void ft_mirror(t_palette *color,t_ray *ray, t_point *base, int *nb_rebond, t_scene *scene)
{
    t_ray mirror;
    t_coord res;

    ft_vectors_mult(&base->normal,0.001, &mirror.origin);
    ft_vectors_add(&mirror.origin,&base->pos, &mirror.origin);
    ft_vectors_mult(&base->normal,2 * ft_scal_produce(&ray->direction,&base->normal),&res);
    ft_vectors_substract(&res,&ray->direction, &mirror.direction); 
    *nb_rebond -= 1;
    ft_color_intensity(color, scene, &mirror, nb_rebond);
}
void ft_glass(t_palette *color,t_ray *ray, t_point *base, int *nb_rebond, t_scene *scene)
{
    t_ray refract_glass;
        double n1;
    double n2;


        if (ft_scal_produce(&ray->direction, &base->normal) > 0)
        {// Sort de la sphere 
            n1 = GLASS;
            n2 = AIR;
        }
        else
        {//Rrentre dans la sphere
            n1 = AIR;
            n2 = GLASS;
            ft_vectors_mult(&base->normal, -1,&base->normal);
        }
        ft_vectors_mult(&base->normal,0.001,&refract_glass.origin);
        ft_vectors_substract(&refract_glass.origin,&base->pos,&refract_glass.origin);
        t_coord tn;
                        ft_vectors_mult(&base->normal, ft_scal_produce(&ray->direction,&base->normal),&tn);
                        ft_vectors_substract(&tn,&ray->direction,&tn);
                        ft_vectors_mult(&tn, n1/n2,&tn);
                        t_coord t_t;
                        double delta;
                        delta = 1-(pow((n1/n2),2)*pow((1-ft_scal_produce(&ray->direction,&base->normal)),2));
                        if (delta < 0)
                        {
                                 base->rgb.r = 1;
                                base->rgb.g = 1;
                                base->rgb.b = 1;
                                return;
                        }
                        ft_vectors_mult(&base->normal,-sqrt(delta),&t_t);
                        ft_vectors_add(&t_t,&tn,&refract_glass.direction)  ;
    
                        *nb_rebond -= 1;
                        ft_color_intensity(color, scene, &refract_glass, nb_rebond);
}



double ft_color_intensity(t_palette *color, t_scene *scene, t_ray *ray, int *nb_rebond)
{
    float V ;
    double dist;
    t_point base;
    t_list *obj;
    t_coord l;
    t_light *tmp;
    if (*nb_rebond == 0)
        return(0);

            if ((obj = ft_color_intensity_2(scene, ray,&base)) != NULL)
            {
                if (obj->magic == 1)
                    ft_mirror(color, ray, &base, nb_rebond, scene);
                else
                    if (obj->magic == 2)
                        ft_glass(color, ray, &base, nb_rebond, scene);
                else
                {
                tmp = *(scene->light);

                while (tmp != NULL)
                {
                    ft_vectors_substract(&base.pos,&tmp->pos, &l);
                    dist = ft_norm2(&l);
                    ft_normalize(&l);
                   V = ft_ombre(&base, dist, scene, tmp);
                    
                    color->intensity +=( V * (ft_scal_produce(&l,&base.normal) + ft_specular(&base, &l, &scene->camera)) / dist) * tmp->i * 1000;
                    color->rgb.r += ((base.rgb.r * 0.5) + (tmp->rgb.r * 0.4) + (scene->amb_light.rgb.r * 0.1)) * (color->intensity + (scene->amb_light.ratio * 0.1));
                    color->rgb.g +=  ((base.rgb.g * 0.5) + (tmp->rgb.g * 0.4) + (scene->amb_light.rgb.g * 0.1)) * (color->intensity + (scene->amb_light.ratio * 0.1));
                    color->rgb.b += ((base.rgb.b * 0.5 )+ (tmp->rgb.b * 0.4) + (scene->amb_light.rgb.b * 0.1)) * (color->intensity  + (scene->amb_light.ratio * 0.1));
                    tmp = tmp->next;
                }
                return (color->intensity);
                }
            }
        return (1);
}