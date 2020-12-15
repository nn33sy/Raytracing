#ifndef FUNCTION_MATHS_H
# define FUNCTION_MATHS_H
# define PI 3.14159265359
typedef  struct s_coord
{
    float x;
    float y;
    float z;
}t_coord;

typedef struct s_ray
{
    t_coord *origin;
    t_coord *direction;
}t_ray;

typedef struct s_sphere
{
    t_coord *origin;
    double  rayon;
}t_sphere;

void    ft_coord(float x, float y,float z, t_coord *pt);
void    ft_vect(t_coord *a, t_coord *b, t_coord *ab);
void    ft_produit_vectoriel(t_coord *a, t_coord *b, t_coord *prod);
void    ft_normalize(t_coord* a);
double    ft_norm2(t_coord* a);
double  ft_scal_produce(t_coord *a, t_coord *b);
void    ft_vectors_div(t_coord *a, float b, t_coord *res);
void    ft_vectors_mult(t_coord *a, float b, t_coord *res);
void    ft_vectors_add(t_coord *a, t_coord *b, t_coord *res);
void    ft_vectors_substract(t_coord *a, t_coord *b, t_coord *res);
int intersection_sphere(t_sphere *s, t_ray *r);
#endif