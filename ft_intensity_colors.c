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
                /*if (tmp->type == 4 && ft_intersection_cylinder((t_cylinder*)tmp->object, ray,base ,&t_min) == 1)
                    min = tmp;*/
                 tmp = tmp->next;
            }
    return(min);
}

double ft_color_intensity(t_palette *color, t_scene *scene, t_ray *ray, int *nb_rebond)
{
    float V ;
    double dist;
    t_point base;  
    t_coord l;
    t_light *tmp;
            if (ft_color_intensity_2(scene, ray,&base) != NULL)
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
        return (1);
}