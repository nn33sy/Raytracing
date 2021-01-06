#include <math.h>
#include "function_maths.h"

int ft_intersection_cylinder(t_cylinder *cy, t_ray *ray,t_coord *pos,t_coord *normal,double *t_min)
{
    t_coord tmp;
    double delt[6];
    double t;
    
    ft_vectors_substract(&cy->base, &ray->origin, &tmp);

    delt[0] = pow(ray->direction.x, 2) + pow(ray->direction.z, 2);
    delt[1] = (2 * ray->direction.x * tmp.x)+ (2 *ray->direction.z * tmp.z);
    delt[2] = pow(tmp.x, 2) + pow(tmp.z, 2) - pow(cy->diameter / 2, 2);
    delt[3] = pow(delt[1], 2) -  4 * delt[0] * delt[2];
    if (delt[3] < 0)
        return (-1);
    delt[4] = (-delt[1] - sqrt(delt[3])) / (2 * delt[0]);
    delt[5] = (-delt[1] + sqrt(delt[3])) / (2 *delt[0]);
    if (delt[4] > 0)
        t = delt[4];
    else
        t = delt[5];
    t_coord pos_bis;
     t_coord mult ;
    ft_vectors_mult(&ray->direction,t, &mult);
    ft_vectors_add(&ray->origin,&mult, &pos_bis);
    if (pos_bis.y > cy->height ) 
        return(-1);
    if (*t_min != -1 && t > *t_min)
        return(-1);
    if (pos == NULL)
        return(0);
    *t_min = t;
    
   
    ft_coord(pos_bis.x, pos_bis.y, pos_bis.z, pos);

     //rx(pos,-3.14 * 90/ 180 );
     t_coord tmmp;
     ft_coord(cy->base.x, pos->y,cy->base.z, &tmmp);
    ft_vectors_substract(&tmmp,pos,normal);
  // rx(pos,3.14 * 90/ 180 );
   //rx(normal,3.14 * 90/ 180 );
    ft_normalize(normal);
    return(1);
}