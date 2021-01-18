#include <math.h>
#include "function_maths.h"

double intersection_sphere(t_sphere *s, t_ray *r, t_coord *pos, t_coord *normal, double *t_min)
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
    if (pos == NULL)
        return(0);
    t_coord mult ;
    ft_vectors_mult(&r->direction,t, &mult);
    ft_vectors_add(&r->origin,&mult, pos);
    ft_vectors_substract(&s->origin,pos,normal);
    ft_normalize(normal);

    return(1);
}