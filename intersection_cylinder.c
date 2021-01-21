#include <math.h>
#include "function_maths.h"
/*
int ft_intersection_cylinder(t_cylinder *cy, t_ray *ray,t_point *base,double *t_min)
{
    t_coord tmp;
    double a,b,c,d;
    double t0,t1,t;

    ft_vectors_substract(&cy->base, &ray->origin, &tmp);
    a = pow(ray->direction.x, 2) + pow(ray->direction.z, 2);
    b = ( ray->direction.x * tmp.x) + (ray->direction.z * tmp.z);
    b *= 2;
    c = pow(tmp.x,2) + pow(tmp.z, 2) - pow((cy->diameter / 2),2);

    d = pow(b,2) - (4 * a *c);
    if (d <= 0)
        return(-1);
    t0 = (-b -sqrt(d))/ ( 2 * a);
    t1 = (-b +sqrt(d))/ ( 2 * a);

    if (t0 > 0)
        t = t0;
    else    
        if (t1 > 0)
            t = t1;
        else
            return(-1);
    *t_min = t;
    if (base == NULL)
        return(0);
    ft_vectors_mult(&ray->direction, t, &base->pos);
    ft_vectors_add(&base->pos, &ray->origin, &base->pos);

t_coord tmmp;
     ft_coord(cy->base.x,base->pos.y, cy->base.z, &tmmp);
    ft_vectors_substract(&tmmp,&base->pos,&base->normal);
    ft_normalize(&base->normal);
    return(1);
}
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
    if (delt[3] < 0)
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
      base->rgb.r = cy->rgb.r;
    base->rgb.g = cy->rgb.g;
    base->rgb.b = cy->rgb.b;
    return(1);
}
/*
int ft_intersection_cylinder(t_cylinder *cy, t_ray *ray,t_point *base,double *t_min)
{
    t_coord tmp;
    double delt[6];
    double t;
    t_coord direc;

   ft_vectors_substract(&cy->base, &ray->origin, &tmp);
    delt[0] = pow(ray->direction.x, 2) + pow(ray->direction.z, 2);
    delt[1] = 2*((ray->direction.x * tmp.x)+ (ray->direction.z * tmp.z));
    delt[2] = pow(tmp.x, 2) + pow(tmp.z, 2) - pow(cy->diameter / 2, 2);
    delt[3] = pow(delt[1], 2) -  (4 *delt[0] * delt[2]);
    if (delt[3] <= 0)
        return (-1);
    delt[4] = (-delt[1] - sqrt(delt[3])) / ( 2*delt[0]);
    delt[5] = (-delt[1] + sqrt(delt[3])) / ( 2 * delt[0]);
        t = delt[4];
    t_coord pos_bis;
     t_coord mult ;
    ft_vectors_mult(&direc,t, &mult);
    ft_vectors_add(&ray->origin,&mult, &pos_bis);
     printf("%f", t);
    if (!(t > 0 && (pos_bis.y - cy->base.y) < cy->height && ((pos_bis.y - cy->base.y) > 0)))
        {
         t = delt[5];
                ft_vectors_mult(&direc,t, &mult);
                ft_vectors_add(&ray->origin,&mult, &pos_bis);
            if (!(t > 0 && (pos_bis.y - cy->base.y) < cy->height && ((pos_bis.y - cy->base.y) > 0)))
                return(-1);

        }

    if (*t_min != -1 && t > *t_min)
        return(-1);
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
/*
double ft_calc_dist(t_point *base, double *x0, double *x1,t_cylinder *cy,t_ray *ray)
{
    double d0;
    double d1;
    double x;
    double d;
    t_coord tmp[5];

    ft_vectors_substract(&ray->origin, &cy->base, &tmp[1]);

    ft_vectors_mult(&ray->direction,*x0,&tmp[0]);
    
    ft_vectors_substract(&tmp[1], &tmp[0], &tmp[2]);
    d0 = ft_scal_produce(&cy->direction, &tmp[2]);

    ft_vectors_mult(&ray->direction,*x1,&tmp[0]);
    ft_vectors_substract(&tmp[1], &tmp[0], &tmp[2]);
    d1 = ft_scal_produce(&cy->direction, &tmp[2]);

    if (x0 < x1 && d0 >= 0 && d0 <= cy->height)
        {
            x = *x0;
            d = d0;
            *x1 = d;
            return(d);
        }
    else
        if (d1 >= 0 && d1 <= cy->height)
        {
            d = d1;
            x = *x1;
            *x0 = x;
            *x1 = d;
            return(d);
        }
        else
            return(-1);

}

int ft_intersection_cylinder(t_cylinder *cy, t_ray *ray,t_point *base,double *t_min)
{
    t_coord deltap;
    t_coord tmp[5];
    double delta[10];
    double t;

    ft_vectors_substract(&cy->base ,&ray->origin, &deltap);

    ft_vectors_mult(&cy->direction, ft_scal_produce(&cy->direction, &ray->direction), &tmp[0]);
    ft_vectors_substract(&tmp[0],&ray->direction, &tmp[1]);

    delta[0] = ft_scal_produce(&tmp[1], &tmp[1]);
    
    ft_vectors_mult(&cy->direction, ft_scal_produce(&deltap, &cy->direction), &tmp[0]);
    ft_vectors_substract(&tmp[0],&deltap, &tmp[3]);

    delta[1] = 2 * ft_scal_produce(&tmp[1],&tmp[3]);
    delta[2] = ft_scal_produce(&tmp[3], &tmp[3]) - pow((cy->diameter / 2),2);
    delta[3] = pow(delta[1], 2) -  (4 * delta[0] * delta[2]);
    if (delta[3] <= 0)
        return (-1);
    delta[5] = (-delta[1] - sqrt(delta[3])) / (2 * delta[0]);
    delta[4] = (-delta[1] + sqrt(delta[3])) / (2 * delta[0]);

    if (delta[4] < 0 && delta[5] < 0)
        return(-1);
    if (ft_calc_dist(base, &delta[4], &delta[5],cy,ray) == -1)
        return(-1);
    double x = delta[4];
    double d = delta[5];
    if (*t_min != -1 && x > *t_min)
        return(-1);
    *t_min = x;
    if (base == NULL)
        return(0);

    ft_vectors_mult(&ray->direction, x, &base->pos);
    ft_vectors_add(&base->pos, &ray->origin, &base->pos);

    ft_vectors_mult(&ray->direction, x, &tmp[0]);
    ft_vectors_mult(&cy->direction,d,&tmp[1]);
    ft_vectors_substract(&tmp[1], &tmp[0], &tmp[3]);
    ft_vectors_substract(&ray->origin, &cy->base, &tmp[4]);
    ft_vectors_substract(&tmp[4], &tmp[3],&base->normal);
    ft_normalize(&base->normal);
    base->rgb.r = cy->rgb.r;
    base->rgb.g = cy->rgb.g;
    base->rgb.b = cy->rgb.b;

    /*
    if (*t_min != -1 && t > *t_min)
        return(-1);
    *t_min = t;
    if (base == NULL)
        return(0);

    ft_vectors_mult(&ray->direction, t, &base->pos);
    ft_vectors_add(&base->pos, &ray->origin, &base->pos);

    t_coord tmmp;
     ft_coord(cy->base.x, base->pos.y,cy->base.z, &tmmp);
    ft_vectors_substract(&tmmp,&base->pos,&base->normal);
    ft_normalize(&base->normal);
    base->rgb.r = cy->rgb.r;
    base->rgb.g = cy->rgb.g;
    base->rgb.b = cy->rgb.b;
return(1);

}*/

int ft_intersection_cylinder(t_cylinder *cy, t_ray *ray,t_point *base,double *t_min)
{
    double a,b,c,delta;
    double m0, m1;
    double m;
    double t0,t1;
    double t;
    t_coord tmp;
    t_coord x;
    
    ft_vectors_substract(&cy->base,&ray->origin,&x);
    ft_normalize(&cy->direction);
    a = ft_scal_produce(&ray->direction, &ray->direction) - pow(ft_scal_produce(&ray->direction, &cy->direction),2);
    b = 2 * ( ft_scal_produce(&ray->direction,&x) - (ft_scal_produce(&ray->direction, &cy->direction) * ft_scal_produce(&x, &cy->direction)));
    c = ft_scal_produce(&x,&x) - pow(ft_scal_produce(&x,&cy->direction),2) - pow((cy->diameter / 2),2);

    delta = pow(b,2) - (4 * a *c);
    if (delta <= 0)
        return(-1);
    t0 = (-b - sqrt(delta)) / (2 * a);
    t1 = (-b + sqrt(delta)) / (2 * a);
    
    if (t0 <= 0 && t1 <= 0)
        return(-1);
    m0 = ft_scal_produce(&ray->direction, &cy->direction) * t0 + ft_scal_produce(&x, &cy->direction);
    m1 = ft_scal_produce(&ray->direction, &cy->direction) * t1 + ft_scal_produce(&x, &cy->direction);
    if (t0 >= 0 && t0 <= t1 && m0 >= 0 && m0 <= cy->height)
        {
            m = m0;
            t = t0;
        }
    else 
        if (t1 >= 0 && m1 >= 0 && m1 <= cy->height)
            {
                 m = m1;
                 t = t1;
            }
        else 
            return(-1);
    if (*t_min != -1 && t > *t_min)
        return(-1);
    *t_min = t;
    if (base == NULL)
        return(0);
    printf("| %f %f %f %f %f %f ? %f %f %f ",a,b,c,delta,t,m, ray->direction.x, ray->direction.y, ray->direction.z);
    ft_vectors_mult(&ray->direction, t, &base->pos);
    ft_vectors_add(&base->pos, &ray->origin, &base->pos);
    ft_vectors_substract(&cy->base, &base->pos, &tmp);
    ft_vectors_mult(&cy->direction, m,&base->normal);
    ft_vectors_substract(&base->normal , &tmp, &base->normal);
    ft_normalize(&base->normal);

    base->rgb.r = cy->rgb.r;
    base->rgb.g = cy->rgb.g;
    base->rgb.b = cy->rgb.b;
    return(1);
    
}