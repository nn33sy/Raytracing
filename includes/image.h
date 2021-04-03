#ifndef IMAGE_H
# define IMAGE_H
# include "minirt.h"

void	ft_create_image(t_vars *vars, t_camera *cam, t_scene *scene);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
void	ft_initialize_img(t_vars *vars, t_data *img, t_scene *scene);
void	ft_initialize_window(t_vars *vars, t_scene *scene);
double	ft_ombre_2(t_scene *scene, double dist, t_ray ray_reflect);
float	ft_ombre(t_point *base, double dist, t_scene *scene, t_light *light);
void	ft_ray_reflect(t_coord *normal, t_coord *light, t_coord *reflect);
double	ft_specular(t_point *base, t_coord *light, t_camera *cam);
void	ft_scale_rgb(t_rgb *rgb);
void	ft_scaling_one_value(double *value);
void	camera_matrice(t_camera *cam);
t_list	*ft_color_intensity_2(t_scene *scene, t_ray *ray, t_point *base);
void	ft_init_color_intensity_2(t_list *tmp, double *t_min,
t_scene *scene);
double	ft_color_intensity(t_palette *color, t_scene *scene, t_ray *ray);
void	ft_put_color_pixel(t_palette *color);
t_list	*ft_color_intensity_2(t_scene *scene, t_ray *ray, t_point *base);
void	ft_send_camera_rays(t_scene *scene, int i, int j, t_camera *ptn);
void	ft_mirror(t_palette *color, t_ray *ray, t_point *base,
t_scene *scene);
void	ft_export_bmp(char *filename, t_vars *vars);
void	ft_clean(t_vars *vars);
void	ft_clean_scene(t_scene *scene);
#endif
