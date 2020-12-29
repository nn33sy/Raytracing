#ifndef FUNCTION_MATHS_H
# define FUNCTION_MATHS_H
#include "libft.h"
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
typedef struct s_rgb
{
    double r;
    double g;
    double b;
}t_rgb;
typedef struct s_palette{
    t_rgb   rgb;
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
    t_rgb   rgb;
    struct s_light *next;
}t_light;

typedef struct s_amb_light
{
    double ratio;
    t_rgb   rgb;
}t_amb_lig;

typedef struct s_sphere
{
    t_coord origin;
    double  rayon;
    int mirror ; //1 oui 0 non
    int clear ; // 1 transparant, 0 non;
    t_rgb rgb;
    int multicolor;
    struct s_sphere *next;

}t_sphere;

typedef struct s_plan
{
    t_coord center;
    t_coord direction;
    t_rgb   rgb;
}t_plan;

typedef struct s_square
{
    t_coord center;
    t_coord direction;
    double side_size;
    t_rgb   rgb;
}t_square;

typedef struct s_triangle
{
    t_coord first;
    t_coord second;
    t_coord third;
    t_rgb   rgb;
}t_triangle;

typedef struct s_cylinder
{
    t_coord center;
    t_coord direction;
    double diameter;
    double height;
    t_rgb rgb;

}t_cylinder;



typedef struct s_scene
{
    t_light *light;
    t_ray   camera;
    int     r_x;
    int     r_y;
    double  fov;
    t_amb_lig amb_light;
    t_list **list;

}t_scene;


void    ft_vectors_mult_by_two(t_coord *a, t_coord *b, t_coord *res);
double  ft_max(double a,const double b);
int intersection_sphere2(t_sphere *s, t_ray *r);
void    ft_coord(double x, double y,double z, t_coord *pt);
void    ft_vect(t_coord *a, t_coord *b, t_coord *ab);
void    ft_produit_vectoriel(t_coord *a, t_coord *b, t_coord *prod);
void    ft_normalize(t_coord* a);
double    ft_norm2(t_coord* a);
double get_random(); 
double generate_nb();
double  ft_scal_produce(t_coord *a, t_coord *b);
void    ft_vectors_div(t_coord *a, double b, t_coord *res);
void    ft_vectors_mult(t_coord *a, double b, t_coord *res);
void    ft_vectors_add(t_coord *a, t_coord *b, t_coord *res);
void    ft_vectors_substract(t_coord *a, t_coord *b, t_coord *res);
int intersection_sphere(t_sphere *s, t_ray *r, t_coord *pos, t_coord *normal, double *t_min);
int ft_visibilite(t_sphere *s, t_ray *r, double *t);
void    ft_vectors_add_const(t_coord *a, double b, t_coord *res);
int main_function(void);
void ft_scaling_one_value(double *value);
int intersection_square(t_square *square, t_ray *ray,t_coord *pos,t_coord *normal,double *t_min);
int intersection_plan(t_plan *plan,t_ray *ray,t_coord *pos,t_coord *normal,double *t_min);
#endif