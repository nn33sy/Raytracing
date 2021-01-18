#include <math.h>
#include "function_maths.h"

int ft_barycentric_triangle(t_coord *pos, t_triangle *tri)
{
    double beta;
    double alpha;
    double sigma;

    beta = ft_calculate_beta(tri, pos);
    sigma = ft_calculate_sigma(tri, pos);
    alpha = ft_calculate_alpha(sigma, beta);
    if (beta < 0 || sigma < 0 || alpha < 0)
        return (-1);
    return (1);
}
double ft_determinant_matrix(t_matrix_two *matrix)
{
    return ((matrix->x1 * matrix->y2) - (matrix->x2 * matrix->y1));

}
double ft_calculate_beta(t_triangle *tri, t_coord *P)
{
    double beta;
    t_matrix_two matrix;
    t_coord tmp[3];

    ft_vectors_substract(&tri->first, P, &tmp[2]);
    ft_vectors_substract(&tri->first, &tri->second, &tmp[0]);
     ft_vectors_substract(&tri->first, &tri->third, &tmp[1]);
    matrix.x1 = ft_scal_produce(&tmp[2], &tmp[0]);
    matrix.x2 = ft_scal_produce(&tmp[1], &tmp[0]);
    matrix.y1 = ft_scal_produce(&tmp[2], &tmp[1]);
    matrix.y2 = ft_norm2(&tmp[1]);
    beta = ft_determinant_matrix(&matrix);
    matrix.x1 = ft_norm2(&tmp[0]);
    matrix.y1 = ft_scal_produce(&tmp[0], &tmp[1]);
    beta /= ft_determinant_matrix(&matrix);
    return(beta);
}

double ft_calculate_sigma(t_triangle *tri, t_coord *P)
{
    double sigma;
    t_matrix_two matrix;
    t_coord tmp[3];

    ft_vectors_substract(&tri->first, P, &tmp[2]);
    ft_vectors_substract(&tri->first, &tri->second, &tmp[0]);
     ft_vectors_substract(&tri->first, &tri->third, &tmp[1]);
    matrix.x1 = ft_norm2(&tmp[0]);
    matrix.y1 = ft_scal_produce(&tmp[0], &tmp[1]);
    matrix.x2 = ft_scal_produce(&tmp[2], &tmp[0]);
    matrix.y2 = ft_scal_produce(&tmp[2], &tmp[1]);
    sigma = ft_determinant_matrix(&matrix);
    matrix.x2 = ft_scal_produce(&tmp[1], &tmp[0]);
    matrix.y2 = ft_norm2(&tmp[1]);
    sigma /= ft_determinant_matrix(&matrix);
    return (sigma);
}
double ft_calculate_alpha(double sigma, double beta)
{
    return (1 - sigma - beta);
}

int ft_intersection_triangle(t_triangle *tri, t_ray *ray, t_point *base, double *t_min)
{
    double t;
    t_coord tmp[3];

    ft_vectors_substract(&tri->first, &tri->second,&tmp[0]);
    ft_vectors_substract(&tri->first, &tri->third,&tmp[1]);
    ft_produit_vectoriel(&tmp[0], &tmp[1], &tmp[2]);
    ft_normalize(&tmp[2]);
    t = intersection_basic(ray, &tmp[2], &(tri->first));
    if (t == -1)
        return(-1);
    if (*t_min != -1 && t > *t_min)
        return(-1);
    ft_vectors_mult(&(ray->direction),t,&tmp[0]);
    ft_vectors_add(&tmp[0], &(ray->origin),&tmp[0]);
    if (ft_barycentric_triangle(&tmp[0] ,tri) == -1)
        return (-1);
    *t_min = t;
    if (base == NULL)
        return(0);
    ft_coord(tmp[2].x, tmp[2].y, tmp[2].z, &base->normal);
    ft_coord(tmp[0].x,tmp[0].y,tmp[0].z,&base->pos);
    base->rgb.r = tri->rgb.r;
    base->rgb.g = tri->rgb.g;
    base->rgb.b = tri->rgb.b;
    return(1);
}
