#include <math.h>
#include "function_maths.h"

void    ft_coord(double x, double y,double z, t_coord *pt) // Determine les coord d checked
{
    pt->x = x;
    pt->y = y;
    pt->z = z;
}
void    ft_vect(t_coord *a, t_coord *b, t_coord *ab) // Definir un vecteur //checked
{
    ab->x = b->x - a->x;
    ab->y = b->y - a->y;
    ab->z = b->z - a->z;
}

void    ft_produit_vectoriel(t_coord *a, t_coord *b, t_coord *prod) // Calcul le produit vectoriel entre deux vecteur a et b
{//checked
    prod->x = (a->y * b->z) - (a->z * b->y);
    prod->y = (a->z * b->x) - (a->x * b->z);
    prod->z = (a->x * b->y) - (a->y * b->x);
}

void    ft_vectors_substract(t_coord *a, t_coord *b, t_coord *res)
{//checked
    res->x = b->x - a->x;
    res->y = b->y - a->y;
    res->z = b->z - a->z;
}


void    ft_vectors_add(t_coord *a, t_coord *b, t_coord *res)
{//checked
    res->x = a->x + b->x;
    res->y = a->y + b->y;
    res->z = a->z + b->z;
}

void    ft_vectors_mult(t_coord *a, double b, t_coord *res)
{//checked
    res->x = a->x * b;
    res->y = a->y * b;
    res->z = a->z * b;
}
void    ft_vectors_mult_by_two(t_coord *a, t_coord *b, t_coord *res)
{//checked
    res->x = a->x * b->x;
    res->y = a->y * b->y;
    res->z = a->z * b->z;
}
void    ft_vectors_div(t_coord *a, double b, t_coord *res)
{//checked
    res->x = a->x / b;
    res->y = a->y / b;
    res->z = a->z / b;
}

double  ft_scal_produce(t_coord *a, t_coord *b)
{//checked
    double res ;
    res = a->x * b->x;
    res += a->y * b->y;
    res += a->z * b->z;
    return (res);
}

double    ft_norm2(t_coord* a)
{
    return (pow(a->x,2) +pow(a->y,2)+pow(a->z,2));
}//checked

void    ft_normalize(t_coord* a)
{//checked
    double norme;
    norme = sqrt(ft_norm2(a));
    a->x /= norme;
    a->y /= norme;
    a->z /= norme;
}
double  ft_max(double a,const double b)
{
    if (a < 0)
        return(0); 
    if (a > b)
        return(b);
    return(a);
}
int ft_visibilite(t_sphere *s, t_ray *r, double *t)
{
    double a = 1;
    double b;
    double c;
    t_coord sub;
    ft_vectors_substract(s->origin, r->origin, &sub); // ?????? pq ca marche 
    b =2 * ft_scal_produce(r->direction, &sub);
    c = ft_norm2(&sub) - pow(s->rayon,2);
    double delta = pow(b,2) - 4*a*c;
    if (delta < 0)
        return (-1);
   double t1 = (-b -sqrt(delta)) / (2*a);
    double t2 = (-b +sqrt(delta)) / (2*a);
    if (t2 < 0)
        return(-1);
    if (t1 > 0)
        *t = t1;
    else
        *t = t2;
    return(1);
}

int intersection_sphere(t_sphere *s, t_ray *r, t_coord *pos, t_coord *normal, double *t_min)
{
    double a = 1;
    double b;
    double c;
    t_coord sub;
    ft_vectors_substract(s->origin, r->origin, &sub); // ?????? pq ca marche 
    b =2 * ft_scal_produce(r->direction, &sub);
    c = ft_norm2(&sub) - pow(s->rayon,2);
    double delta = pow(b,2) - 4*a*c;
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
    t_coord mult ;
    ft_vectors_mult(r->direction,t, &mult);
    ft_vectors_add(r->origin,&mult, pos);
    ft_vectors_substract(s->origin,pos,normal);
    ft_normalize(normal);
    return(1);
}



/*
int main()
{
    t_coord *a;
    a =malloc(sizeof(t_coord));
    ft_coord(5,5,-5,a);
    printf("%f %f %f\n",a->x, a->y,a->z);
    t_sphere s;
    s.origin = a;
    s.rayon = 5;

    t_ray t;
    t_coord *normal = malloc(sizeof(t_coord));
    t_coord *pos= malloc(sizeof(t_coord));
    t.origin = malloc(sizeof(t_coord));
    t.direction = malloc(sizeof(t_coord));
    ft_coord(0,0,0,t.origin);
    ft_coord(5,5,-10,t.direction);
    printf("%d",intersection_sphere(&s,&t,pos,normal));
  t_light light;
  light.pos = malloc(sizeof(t_coord));
   ft_coord(15,60, -40,light.pos);
   light.i = 10000;
t_coord *l =malloc(sizeof(t_coord));
double intensity;
                double dist;
                ft_vectors_substract(light.pos, pos, l);
                dist = ft_norm2(l);
                ft_normalize(l);
                intensity = (light.i * ft_scal_produce(l,normal)) / dist ;
                printf("%f",intensity);
}*/