#include <math.h>
#include "function_maths.h"

double intersection_sphere(t_sphere *s, t_ray *r, t_point *base, double *t_min)
{
    double a = 1;
    double b;
    double c;
    t_coord sub;
    ft_vectors_substract(&s->origin, &r->origin, &sub); 
    b =2 * ft_scal_produce(&r->direction, &sub);
    c = ft_norm2(&sub) - pow(s->rayon,2);
    double delta = pow(b,2) - 4 * a * c;
    if (delta < 0)
        return (-1);
   double t1 = (-b -sqrt(delta)) / (2*a);
    double t2 = (-b +sqrt(delta)) / (2*a);
    if (t2 < 0)
        return(-1);
    double t;
    if (t1 > 0)
        t = t1;
    else
        t = t2;
    if (*t_min != -1 && t > *t_min)
        return(-1);
    else
        *t_min = t;
    if (base == NULL)
        return(0);
    t_coord mult ;
    ft_vectors_mult(&r->direction,t, &mult);
    ft_vectors_add(&r->origin,&mult, &base->pos);
    ft_vectors_substract(&s->origin, &base->pos, &base->normal);
    ft_normalize(&base->normal);
    base->rgb.r = s->rgb.r;
    base->rgb.g = s->rgb.g;
    base->rgb.b = s->rgb.b;

    return(1);
}