#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mlx.h"
#include "function_maths.h"

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

int             main(void)
{
    t_vars      vars;
    t_data  img;
    int     i= 0;
    int     j = 0;
    int h = 400;
    int w = 400;
    double fov = 60 *PI / 180;
    t_sphere *sphere;

    sphere->rayon = 20;
    ft_coord(0,0, -55,sphere->origin);


    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, h, w, "Hello world!");
    t_ray *ray;
    ray = malloc(sizeof(t_ray));
    ft_coord(0, 0,0, ray->origin);


while (i < height)
{
    while (j < width)
    {
        ft_coord(j-(w/2),i-(h/2), -w/(2*tan(fov/2)), ray->direction);
        ft_normalize(ray->direction);
        
    }
}
    my_mlx_pixel_put(&img, i, j, 0x00FF0000);
    
     mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
     mlx_loop(vars.mlx);
}