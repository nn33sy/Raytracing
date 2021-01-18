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

#endif