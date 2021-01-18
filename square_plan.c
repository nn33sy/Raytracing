#include <math.h>
#include "function_maths.h"

double intersection_basic(t_ray *ray, t_coord *direction, t_coord *center)
{
    double t;
    t_coord a;
    double essai;
    if (ft_scal_produce(&(ray->direction),direction) == 0)
        return (-1);
    essai = ft_scal_produce(&(ray->direction),direction) / (sqrt(ft_norm2(&ray->direction)) * sqrt(ft_norm2(direction)));
    essai = acos(essai) * (180 / PI);
    ft_vectors_substract(&(ray->origin),center, &a);
    t = ft_scal_produce(&a,direction);
    t /= ft_scal_produce(&(ray->direction),direction);
    if (t > 0)
        return(t);
    return(-1);
}

int intersection_plan(t_plan *plan,t_ray *ray,t_coord *pos,t_coord *normal,double *t_min)
{
    double t;
    t = intersection_basic(ray,&(plan->direction), &(plan->center));
    if (t == -1)
        return(-1);
    if (*t_min != -1 && t > *t_min)
        return(-1);
    *t_min = t;
    if (normal == NULL)
        return(0);
    ft_coord(plan->direction.x,plan->direction.y,plan->direction.z,normal);
    ft_vectors_mult(&(ray->direction), t,pos);
    ft_vectors_add(pos, &(ray->origin),pos);
    return(1);
}

int intersection_square(t_square *square, t_ray *ray,t_coord *pos,t_coord *normal,double *t_min)
{
    double t;
    t_coord proj;
    t = intersection_basic(ray, &(square->direction), &(square->center));
    if (t == -1)
        return(-1);
    if (*t_min != -1 && t > *t_min)
        return(-1);
    ft_vectors_mult(&(ray->direction),t,&proj);
    ft_vectors_add(&proj, &(ray->origin),&proj);
    if (ft_abs(proj.x - square->center.x) > (square->side_size)/2)
        return(-1);
    if (ft_abs(proj.y - square->center.y) > (square->side_size)/2)
        return(-1);
    if (ft_abs(proj.z - square->center.z) > (square->side_size)/2)
        return(-1);
    *t_min = t;
    if (normal == NULL)
        return(0);
    ft_coord(square->direction.x,square->direction.y,square->direction.z,normal);
    ft_coord(proj.x,proj.y,proj.z,pos);
    return(1);
}
