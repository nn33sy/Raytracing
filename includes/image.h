#ifndef IMAGE_H
# define IMAGE_H
typedef struct    s_vars
{
    void          *mlx;
    void          *win;
}                 t_vars;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;


void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
void ft_initialize_img(t_vars *vars, t_data *img, t_scene *scene);
double ft_ombre_2(t_scene *scene, double dist, t_ray ray_reflect);
float ft_ombre(t_point *base, double dist, t_scene *scene, t_light *light);
void ft_ray_reflect(t_coord *normal, t_coord *light, t_coord *reflect);
double ft_specular(t_point *base, t_coord *light, t_camera *cam);
void ft_scale_rgb(t_rgb *rgb);
void ft_scaling_one_value(double *value);
void camera_matrice(t_scene *scene);
t_list *ft_color_intensity_2(t_scene *scene, t_ray *ray, t_point *base);
double ft_color_intensity(t_palette *color, t_scene *scene, t_ray *ray, int *nb_rebond);
void ft_put_color_pixel(t_palette *color, t_scene *scene);
t_list *ft_color_intensity_2(t_scene *scene, t_ray *ray, t_point *base);
void ft_send_camera_rays(t_scene *scene, int i, int j, t_palette *color_f);

#endif