/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_maths.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:05:56 by how-choongi       #+#    #+#             */
/*   Updated: 2021/04/07 19:05:57 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_MATHS_H
# define FUNCTION_MATHS_H
# define PI 3.14159265359
# define NRAYS 1
# define GLASS 1.3
# define AIR 1.0
# include "minirt.h"

void	ft_vectors_mult_by_two(t_coord *a, t_coord *b, t_coord *res);
double	ft_max(double a, const double b);
void	ft_coord(double x, double y, double z, t_coord *pt);
void	ft_vect(t_coord *a, t_coord *b, t_coord *ab);
void	ft_produit_vectoriel(t_coord *a, t_coord *b, t_coord *prod);
void	ft_normalize(t_coord *a);
double	ft_norm2(t_coord *a);
double	ft_scal_produce(t_coord *a, t_coord *b);
void	ft_vectors_div(t_coord *a, double b, t_coord *res);
void	ft_vectors_mult(t_coord *a, double b, t_coord *res);
void	ft_vectors_add(t_coord *a, t_coord *b, t_coord *res);
void	ft_vectors_substract(t_coord *a, t_coord *b, t_coord *res);
double	intersection_sphere(t_sphere *s, t_ray *r,
			t_point *base, double *t_min);
int		ft_visibilite(t_sphere *s, t_ray *r, double *t);
void	ft_vectors_add_const(t_coord *a, double b, t_coord *res);
int		main_function(char *file_src, int photo);
char	*ft_parsing_double(char *line, double *nb);
void	ft_scaling_one_value(double *value);
double	ft_determinant_matrix(t_matrix_two *matrix);
int		intersection_square(t_square *square, t_ray *ray,
			t_point *base, double *t_min);
int		intersection_plan(t_plan *plan, t_ray *ray,
			t_point *base, double *t_min);
double	ft_calculate_sigma(t_triangle *tri, t_coord *p);
double	ft_calculate_beta(t_triangle *tri, t_coord *p);
int		ft_barycentric_triangle(t_coord *pos, t_triangle *tri);
double	ft_calculate_alpha(double sigma, double beta);
void	ft_vectors_translate(t_coord *a, t_coord *b);
int		ft_intersection_triangle(t_triangle *tri, t_ray *ray,
			t_point *base, double *t_min);
void	rx(t_coord *coord, double x);
void	ry(t_coord *vect, double y);
void	rz(t_coord *vect, double z);
void	rot(t_coord *vect, t_coord *angle);
void	anti_rot(t_coord *vect, t_coord *angle);
double	ft_abs(double x);
int		ft_intersection_cylinder(t_cylinder *cy,
			t_ray *ray, t_point *base, double *t_min);
double	intersection_basic(t_ray *ray, t_coord *direction, t_coord *center);
#endif
