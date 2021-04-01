#include "minirt.h"

void ft_free_camera(t_camera *cam)
{
    if (cam->next != NULL)
        ft_free_camera(cam->next);
    free(cam);
}

void ft_free_light(t_light *light)
{
    if (light->next != NULL)
        ft_free_light(light->next);
    free(light);
}

void ft_free_list(t_list *list)
{
    if (list->next != NULL)
        ft_free_list(list->next);
    if (list->object != NULL)
        free(list->object);
    free(list);
}
void ft_clean_scene(t_scene *scene)
{
    if (scene->camera != NULL)
    {
        if (*(scene->camera) != NULL)
            ft_free_camera(*(scene->camera));
        free(scene->camera);
    }
    if (scene->light != NULL)
    {
        if (*(scene->light) != NULL)
            ft_free_light(*(scene->light));
        free(scene->light);
    }
    if (scene->list != NULL)
    {
        if (*(scene->list) != NULL)
            ft_free_list(*(scene->list));
        free(scene->list);
    }
}


void ft_clean(t_vars *vars)
{
    if (vars->scene != NULL)
    {
        ft_clean_scene(vars->scene);
        free(vars->scene);
    }
    if (vars->mlx != NULL)
        free(vars->mlx);
    if (vars->win != NULL)
        free(vars->win);
}