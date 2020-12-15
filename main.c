#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mlx.h"

#define PI 3.14159265

//compiler avec gcc -I minilibx-linux main.c -L minilibx-linux -lmlx -lXext -lX11
typedef struct    s_vars
{
    void          *mlx;
    void          *win;
}                 t_vars;
/*

typedef struct  s_img {
    void        *img; 
    char        *addr;// Adresse memoire dans lequele on va muter les bites
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_img;
int		create_trgb(int t, int r, int g, int b) // Mettre RGB entre 0 et 255 par decalage de bits
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void            my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int main(void)
{
    data_t        mlx;
    t_img    img; //pointeur image

    mlx.mlx_ptr = mlx_init(); // Connecte avec la systeme graphique, mlx ptr garde ou est situé notr MLX

   // Writing pixels to a image
    img.img = mlx_new_image(mlx.mlx_ptr, 480,680); // Génére une image pour dessiner des pixels

    
    ** After creating an image, we can call `mlx_get_data_addr`, we pass
    ** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
    ** then be set accordingly for the *current* data address.

    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);

    printf("%d,  %d   %d",img.bits_per_pixel, img.line_length, img.endian);
    //bits per pixel 32 , line length 1920 endian 0
    //line length != width image 480

    my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
    mlx_put_image_to_window(mlx.mlx_ptr, mlx.mlx_win, img.img, 0, 0);
    // mlx_loop(data.mlx_ptr);
  data.mlx_win = mlx_new_window(data.mlx_ptr, 480, 680, "Hello world"); // Va créer une fenetre
   mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}
*/

#include <mlx.h>


typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;



int		create_trgb(int t, int r, int g, int b) // Mettre RGB entre 0 et 255 par decalage de bits
{
	return(t << 24 | r << 16 | g << 8 | b);
}
void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}



int             key_hook(int keycode, t_vars *vars)
{
    printf("Hello from key_hook!\n");
}
int             main(void)
{
    t_vars      vars;
    t_data  img;


    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 400, 400, "Hello world!");
  //  mlx_key_hook(vars.win, key_hook, &vars);
  img.img = mlx_new_image(vars.mlx, 400, 400);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);





    int i = 0;
    int j = 0;



    while (i < 400)
    {
        while (j < 400)
        {

           // if  (double_i + double_j <= d)
            if  (( ((i - 200)*(i-200)) + ((j - 200) *(j-200))) <= (100*100))
                my_mlx_pixel_put(&img, i, j, 0x00FF0000);

            j++;


        }
        i++;
        j =0;
    }


    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

    mlx_loop(vars.mlx);
}