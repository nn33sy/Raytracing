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

typedef  struct s_coord
{
    int x;
    int y;
    int z;
}t_coord;
typedef struct s_triangle{
    t_coord a1;
    t_coord a2;
    t_coord a3;
}t_triangle;

typedef struct s_vecteur{
    int x;
    int y;
    int z;
}t_vect;

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

t_coord *ft_produit_vectoriel(t_vect *a, t_vect *b)
{
    t_coord *c;
    c = malloc(sizeof(t_coord));
    c->x = (a->y * b->z) - (a->z * b->y);
    c->y = (a->z * b->x) - (a->x * b->z);
    c->z = (a->x * b->y) - (a->y * b->x);
    return(c);
}
t_vect *ft_vect(t_coord *a, t_coord *b)
{
    t_vect *c =malloc(sizeof(t_vect));
    c->x = b->x - a->x;
    c->y = b->y - a->y;
    c->z = b->z - a->z;
    return (c);
}
t_coord *ft_coord(int x, int y,int z)
{
    t_coord *pt;
    pt = malloc(sizeof(t_coord));
    pt->x = x;
    pt->y = y;
    pt->z = z;
    return(pt);
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
    mlx_key_hook(vars.win, key_hook, &vars);
/*    img.img = mlx_new_image(mlx, 400, 400);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);


    t_coord *A;
    t_coord *B;
    t_coord *C;
    A=ft_coord(2,3,4);
    B = ft_coord(5,6,7);
    C =ft_coord(3,3,3);
    t_vect *ab;
    t_vect *ac;

    ab = ft_vect(A,B);
    ac = ft_vect(A,C);
    t_coord *produit;
    produit = ft_produit_vectoriel(ab,ac);


    int i = 0;
    int j = 0;
t_coord *M;
M =malloc(t_coord);


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

     my_mlx_pixel_put(&img, 5, 50, 0x00FF0000);
     my_mlx_pixel_put(&img, 5, 51, 0x00FF0000);
*/

//    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

    mlx_loop(vars.mlx);
}