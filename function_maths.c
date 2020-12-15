#include <math.h>
#include "function_maths.h"

void    ft_coord(float x, float y,float z, t_coord *pt) // Determine les coord d
{
    t_coord *pt;
    pt->x = x;
    pt->y = y;
    pt->z = z;
}
void    ft_vect(t_coord *a, t_coord *b, t_coord *ab) // Definir un vecteur
{
    ab->x = b->x - a->x;
    ab->y = b->y - a->y;
    ab->z = b->z - a->z;
}

void    ft_produit_vectoriel(t_coord *a, t_coord *b, t_coord *prod) // Calcul le produit vectoriel entre deux vecteur a et b
{
    prod->x = (a->y * b->z) - (a->z * b->y);
    prod->y = (a->z * b->x) - (a->x * b->z);
    prod->z = (a->x * b->y) - (a->y * b->x);
}

void    ft_vectors_substract(t_coord *a, t_coord *b, t_coord *res)
{
    res->x = a->x - b->x;
    res->y = a->y - b->y;
    res->z = a->z - b->z;
}


void    ft_vectors_add(t_coord *a, t_coord *b, t_coord *res)
{
    res->x = a->x + b->x;
    res->y = a->y + b->y;
    res->z = a->z + b->z;
}

void    ft_vectors_mult(t_coord *a, float b, t_coord *res)
{
    res->x = a->x * b;
    res->y = a->y * b;
    res->z = a->z * b;
}
void    ft_vectors_div(t_coord *a, float b, t_coord *res)
{
    res->x = a->x / b;
    res->y = a->y / b;
    res->z = a->z / b;
}

void    ft_scal_produce(t_coord *a, t_coord *b, t_coord *res)
{
    res->x = a->x * b->x;
    res->y = a->y * b->y;
    res->z = a->z * b->z;
}

double    ft_norm2(t_coord* a)
{
    return (pow(a->x,2) +pow(a->y,2),pow(a->z,2))
}

void    ft_normalize(t_coord* a)
{
    double norme;
    norme = ft_norm2(a);
    a->x /= norme;
    a->y /= norme;
    a->z /= norme;
}

int intersection_sphere(t_sphere *s, t_ray *r)
{
    double a = 1;
    t_coord *sub;
    double b = 2 * ft_scal_produce(r->direction, ft_substract(r->origin - s->origin,) )
}