#include <math.h>
#include "function_maths.h"

void    ft_coord(double x, double y,double z, t_coord *pt)
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
void    ft_vectors_translate(t_coord *a, t_coord *b)
{
    a->x = a->x + b->x;
    a->y = a->y + b->y;
    a->z = a->z + b->z;
}

void    ft_vectors_mult(t_coord *a, double b, t_coord *res)
{//checked
    res->x = a->x * b;
    res->y = a->y * b;
    res->z = a->z * b;
}
void    ft_vectors_add_const(t_coord *a, double b, t_coord *res)
{//checked
    res->x = a->x + b;
    res->y = a->y + b;
    res->z = a->z + b;
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
double  ft_max(double a, double b)
{
    if (a > b)
        return(a);
    return(b);
}

double ft_abs(double x)
{
    if (x < 0)
        return(-x);
    return(x);
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