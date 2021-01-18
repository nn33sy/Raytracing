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
            if (ft_color_intensity_2(scene, ray,&base) != NULL)
            {
    
                ft_vectors_substract(&base.pos,&scene->light->pos, &l);
                dist = ft_norm2(&l);
                ft_normalize(&l);
                V = ft_ombre(&base, dist, scene);
                color->intensity += V * (ft_scal_produce(&l,&base.normal) / dist) * scene->light->i * 100000;
                if (V == 1)
                    color->intensity += ft_specular(&base, &l, &scene->camera);
                color->rgb.r+= base.rgb.r;
                color->rgb.g+=  base.rgb.g;
                color->rgb.b += base.rgb.b;
                return (color->intensity);
                }
        return (1);
}