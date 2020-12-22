#ifndef FUNCTION_MATHS_H
# define FUNCTION_MATHS_H
# define PI 3.14159265359
# define nrays 5
# define GLASS 1.3
# define AIR 1.0
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
typedef  struct s_coord
{
    double x;
    double y;
    double z;
}t_coord;
typedef struct t_rgb
{
    double r;
    double g;
    double b;
}s_rgb;
typedef struct s_palette{
    s_rgb   rgb;
    double intensity;
}t_palette;

typedef struct s_ray
{
    t_coord origin;
    t_coord direction;
}t_ray;


typedef struct s_light
{
    t_coord pos;
    double     i;
    s_rgb   rgb;
    struct s_light *next;
}t_light;

typedef struct s_amb_light
{
    double ratio;
    s_rgb   rgb;
}t_amb_lig;

typedef struct s_sphere
{
    t_coord origin;
    double  rayon;
    int mirror ; //1 oui 0 non
    int clear ; // 1 transparant, 0 non;
    double r;
    double g;
    double b; //x -> R y--> G z-->B
    struct s_sphere *next;
    int multicolor;

}t_sphere;

typedef struct s_scene
{
    t_light *light;
    t_ray   camera;
    int     r_x;
    int     r_y;
    double  fov;
    t_amb_lig amb_light;

}t_scene;


void    ft_vectors_mult_by_two(t_coord *a, t_coord *b, t_coord *res);
double  ft_max(double a,const double b);
int intersection_sphere2(t_sphere *s, t_ray *r);
void    ft_coord(double x, double y,double z, t_coord *pt);
void    ft_vect(t_coord *a, t_coord *b, t_coord *ab);
void    ft_produit_vectoriel(t_coord *a, t_coord *b, t_coord *prod);
void    ft_normalize(t_coord* a);
double    ft_norm2(t_coord* a);
double get_random(); //Anti Aliasing
double generate_nb();//Anti Aliasing
double  ft_scal_produce(t_coord *a, t_coord *b);
void    ft_vectors_div(t_coord *a, double b, t_coord *res);
void    ft_vectors_mult(t_coord *a, double b, t_coord *res);
void    ft_vectors_add(t_coord *a, t_coord *b, t_coord *res);
void    ft_vectors_substract(t_coord *a, t_coord *b, t_coord *res);
int intersection_sphere(t_sphere *s, t_ray *r, t_coord *pos, t_coord *normal, double *t_min);
int ft_visibilite(t_sphere *s, t_ray *r, double *t);
void    ft_vectors_add_const(t_coord *a, double b, t_coord *res);
#endif