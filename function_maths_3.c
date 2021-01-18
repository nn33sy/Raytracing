#include <math.h>
#include "function_maths.h"

double  ft_scal_produce(t_coord *a, t_coord *b)
{
    double res ;
    res = a->x * b->x;
    res += a->y * b->y;
    res += a->z * b->z;
    return (res);
}

double    ft_norm2(t_coord* a)
{
    return (pow(a->x,2) +pow(a->y,2)+pow(a->z,2));
}

void    ft_normalize(t_coord* a)
{
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