#include <math.h>
#include "function_maths.h"

int ft_intersection_cylinder(t_cylinder *cy, t_ray *ray,t_point *base,double *t_min)
{
    t_coord tmp;
    double delt[6];
    double t;
    t_coord direc;

    ft_coord(ray->direction.x,ray->direction.y,ray->direction.z,&direc);
    //ry(&direc,3.14 * 10/ 180);
    ft_vectors_substract(&cy->base, &ray->origin, &tmp);
    delt[0] = pow(direc.x, 2) + pow(direc.z, 2);
    delt[1] = (direc.x * tmp.x)+ (direc.z * tmp.z);
    delt[2] = pow(tmp.x, 2) + pow(tmp.z, 2) - pow(cy->diameter / 2, 2);
    delt[3] = pow(delt[1], 2) -  delt[0] * delt[2];
    if (delt[3] <= 0)
        return (-1);
    delt[4] = (-delt[1] - sqrt(delt[3])) / (delt[0]);
    delt[5] = (-delt[1] + sqrt(delt[3])) / (delt[0]);
        t = delt[4];
    t_coord pos_bis;
     t_coord mult ;
    ft_vectors_mult(&direc,t, &mult);
    ft_vectors_add(&ray->origin,&mult, &pos_bis);
    if ((pos_bis.y - cy->base.y) > cy->height || ((pos_bis.y - cy->base.y) < 0))
        {
            t = delt[5];
                ft_vectors_mult(&direc,t, &mult);
    ft_vectors_add(&ray->origin,&mult, &pos_bis);
            if ((pos_bis.y - cy->base.y) > cy->height || ((pos_bis.y - cy->base.y) < 0))
                return(-1);

        }
    if (*t_min != -1 && t > *t_min)
        return(-1);
    ft_coord(direc.x,direc.y,direc.z,&direc);
    *t_min = t;
    if (base == NULL)
        return(0);
    ft_coord(pos_bis.x, pos_bis.y, pos_bis.z, &base->pos);
     //rx(pos,-3.14 * 90/ 180 );
     t_coord tmmp;
     ft_coord(cy->base.x, base->pos.y,cy->base.z, &tmmp);
    ft_vectors_substract(&tmmp,&base->pos,&base->normal);
  // rx(pos,3.14 * 90/ 180 );
   //rx(normal,3.14 * 90/ 180 );
    ft_normalize(&base->normal);
    return(1);
}