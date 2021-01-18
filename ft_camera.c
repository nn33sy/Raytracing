#include "function_maths.h"
#include "get_next_line.h"
#include "libft.h"
#include "parsing.h"
#include "image.h"

void camera_matrice(t_scene *scene)
{
    t_coord tmp;

    ft_normalize( &scene->camera.forward);
    ft_coord(-scene->camera.direction.x, -scene->camera.direction.y, -scene->camera.direction.z, &scene->camera.forward);
    if (scene->camera.direction.x == 0 && scene->camera.direction.z == 0 && (scene->camera.direction.y == 1 || scene->camera.direction.y == -1))
            ft_coord(1, 0, 0, &scene->camera.right);
    else
    {
        ft_coord(0, 1, 0, &tmp);
        ft_produit_vectoriel(&tmp, &scene->camera.forward, &scene->camera.right);
    }
    ft_produit_vectoriel(&scene->camera.forward, &scene->camera.right, &scene->camera.up);
}

void ft_send_ray(t_scene *scene)
{
    
}