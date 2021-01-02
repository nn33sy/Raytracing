#include "parsing.h"
#include "libft.h"

int ft_r(char *line, t_scene *scene)
{
    if (*line == 'R')
        line++;
    else 
        return(-1);
    if ((scene->r_x= ft_atoi_rt(line)) == 0)
        return(-1);
    while (*line >= '0' && *line <= '9')
        line++;
    if ((scene->r_y= ft_atoi_rt(line)) == 0)
        return(-1);
    return(1);
}
char *ft_parsing_position(char *line, t_coord *coord)
{
    coord->x = ft_atoi_rt(line);
    while (*line && *line != ',')
        line++;
    line++;
    coord->y = ft_atoi_rt(line);
    while (*line && *line != ',')
        line++;
    line++;
     coord->z = ft_atoi_rt(line);
    while (*line && (((*line >= '0') && (*line <= '9')) || (*line == '.') || (*line == '-')))
        line++;
    return(line);
}
char *ft_parsing_rgb(t_rgb *rgb, char *line)
{
    rgb->r = ft_atoi_rt(line);
    while (*line && (*line != ','))
        line++;
    if (*line)
        line++;
    rgb->g = ft_atoi_rt(line);
     while (*line && (*line != ','))
        line++;
    if (*line)
        line++;
     rgb->b = ft_atoi_rt(line);
    while (*line && ((*line >= '0') && (*line <= '9')))
        line++;
    return(line);
}

int ft_c(char *line, t_scene *scene)
{  
    if (*line == 'c')
        line++;
    else 
        return(-1);
    line = ft_parsing_position(line, &scene->camera.origin);
    line = ft_parsing_position(line, &scene->camera.direction);
    line = ft_parsing_double(line, &scene->fov);
    scene->fov = (scene->fov * 3.14)/180;
    return(1);
}

int ft_a(char *line, t_scene *scene)
{
    if (*line == 'A')
        line++;
    else
        return(-1);
    line = ft_parsing_double(line, &scene->fov);
    ft_parsing_rgb(&scene->amb_light.rgb,line);
    return(1);
}
int ft_l(char *line,t_light *light)
{
    if (*line != 'l')
        return (-1);
    line++;
    line = ft_parsing_position(line,&light->pos);
    line = ft_parsing_double(line, &light->i);
    ft_parsing_rgb(&light->rgb,line);
    return(1);

}
int ft_sp(char *line, t_scene *scene)
{
    if (*line != 's')
        return(-1);
    line++;
    if (*line != 'p')
        return(-1);
    line++; 
    t_sphere *sphere = malloc(sizeof(t_sphere));
    line = ft_parsing_position(line,&sphere->origin);
    line = ft_parsing_double(line, &sphere->rayon);
    line = ft_parsing_rgb( &sphere->rgb,line);
    ft_lstadd_front(scene->list,ft_lstnew((void *)sphere, 0));
    return(1);
}
int ft_p(char *line, t_scene *scene)
{
    if (*line != 'p')
        return(-1);
    line++;
    if (*line != 'l')
        return(-1);
    line++; 
    t_plan *plan = malloc(sizeof(t_plan));
    line = ft_parsing_position(line,&plan->center);
    line = ft_parsing_position(line,&plan->direction);
    line = ft_parsing_rgb( &plan->rgb,line);
    ft_lstadd_front(scene->list,ft_lstnew((void *)plan, 1));
    return(1);
}
int ft_sq(char *line, t_scene *scene)
{
    if (*line != 's')
        return(-1);
    line++;
    if (*line != 'q')
        return(-1);
    line++;
    t_square *square = malloc(sizeof(t_square));
    line = ft_parsing_position(line,&square->center);
    line = ft_parsing_position(line,&square->direction);
    line = ft_parsing_double(line, &square->side_size);
    line = ft_parsing_rgb( &square->rgb,line);
    ft_lstadd_front(scene->list,ft_lstnew((void *)square, 2));
    return (1);
}
int ft_tr(char *line, t_scene *scene)
{
    if (*line != 't')
        return(-1);
    line++;
    if (*line != 'r')
        return(-1);
    line++;
    t_triangle *triangle =malloc(sizeof(t_triangle));
    line = ft_parsing_position(line,&triangle->first);
    line = ft_parsing_position(line,&triangle->second);
    line = ft_parsing_position(line,&triangle->third);
    line = ft_parsing_rgb(&triangle->rgb,line);
    ft_lstadd_front(scene->list,ft_lstnew((void *)triangle, 3));
    return (1);
}

char *ft_parsing_double(char *line, double *nb)
{
    while (*line && (*line == ' '))
        line++;
    *nb = ft_atoi_rt(line);
    while (*line && ((*line >= '0' && *line <= '9') || (*line == '.')))
        line++;
    return(line);
}

int ft_cy(char *line, t_scene *scene)
{
    if (*line != 'c')
        return(-1);
    line++;
    if (*line != 'y')
        return(-1);
    line++;
    t_cylinder *cylinder =malloc(sizeof(t_cylinder));
    line = ft_parsing_position(line,&cylinder->center);
    line = ft_parsing_position(line,&cylinder->direction);
    line = ft_parsing_rgb(&cylinder->rgb, line);
    line = ft_parsing_double(line, &cylinder->diameter);
    line = ft_parsing_double(line, &cylinder->height);
    ft_lstadd_front(scene->list,ft_lstnew((void *)cylinder, 4));
    return(1);
}

int ft_heart(char *line, t_scene *scene)
{
    if (*line != '<')
        return(-1);
    line++;
    if (*line != '3')
        return(-1);
    line++;
    t_heart *heart = malloc(sizeof(t_heart));
    while (*line && (*line == ' '))
        line++;
    line = ft_parsing_position(line,&heart->center);
    while (*line && (*line == ' '))
        line++;
    line = ft_parsing_rgb(&heart->rgb,line);
    ft_lstadd_front(scene->list,ft_lstnew((void *)heart, 5));
    return(1);
}

t_scene *main_parsing(void)
{
    char *line[2000];
    int i;
    int nb;
    i = 0;
int fd;
fd=open("scenes/scene.rt",O_RDONLY);
while (get_next_line(fd, &line[i]) > 0)
    i++;
nb = ++i ;
i = 0;

t_scene *scene;
scene = malloc(sizeof(t_scene));

t_light *light = malloc(sizeof(t_light));
scene->light = light;
ft_r(line[0],scene);
ft_a(line[1],scene);
ft_c(line[3],scene);
ft_l(line[4],light);

scene->list = malloc(sizeof(t_list *));
i = 6;
while (i < nb)
{
    if (line[i][0] == 's' && line[i][1] == 'p')
        ft_sp(line[i],scene);
    if (line[i][0] == 's' && line[i][1] == 'q')
           ft_sq(line[i],scene); 
    if (*line[i] == 'p')
        ft_p(line[i],scene);
    if (line[i][0] == 't' && line[i][1] == 'r')
           ft_tr(line[i],scene);
    if (line[i][0] == '<' && line[i][1] == '3')
        ft_heart(line[i],scene);
    if (line[i][0] == 'c' && line[i][1] == 'y')
        ft_cy(line[i],scene);  
    i++;
}


printf("ok");
t_list *tmp= *(scene->list);
while (tmp != NULL)
{

/*
if (tmp->type == 2)
{
    t_square *square= (t_square *)tmp->object;
    printf("%f\n",square->center.x);
    printf("%f\n",square->center.y);
    printf("%f\n",square->center.z);
     printf("%f\n",square->direction.x);
     printf("%f\n",square->direction.y);
     printf("%f\n",square->direction.z);
     printf("%f\n",square->rgb.r);
     printf("%f\n",square->rgb.g);
     printf("%f\n",square->rgb.b);
     printf("%f\n",square->side_size);
}

if (tmp->type == 2)
{
    t_plan *plan= (t_plan *)tmp->object;
    printf("%f\n",plan->center.x);
    printf("%f\n",plan->center.y);
    printf("%f\n",plan->center.z);
     printf("%f\n",plan->direction.x);
     printf("%f\n",plan->direction.y);
     printf("%f\n",plan->direction.z);
     printf("%f\n",plan->rgb.r);
     printf("%f\n",plan->rgb.g);
     printf("%f\n",plan->rgb.b);
}
if (tmp->type == 3)
{
    t_triangle *t= (t_triangle *)tmp->object;
    printf("%f\n",t->first.x);
    printf("%f\n",t->first.y);
    printf("%f\n",t->first.z);
    printf("%f\n",t->second.x);
    printf("%f\n",t->second.y);
    printf("%f\n",t->second.z);
    printf("%f\n",t->third.x);
    printf("%f\n",t->third.y);
    printf("%f\n",t->third.z);
     printf("%f\n",t->rgb.r);
     printf("%f\n",t->rgb.g);
     printf("%f\n",t->rgb.b);
}*/
if (tmp->type == 4)
{
    t_cylinder *cyl= (t_cylinder *)tmp->object;
    printf("%f\n",cyl->center.x);
    printf("%f\n",cyl->center.y);
    printf("%f\n\n",cyl->center.z);
    printf("%f\n",cyl->direction.x);
    printf("%f\n",cyl->direction.y);
    printf("%f\n",cyl->direction.z);
    printf("%f\n",cyl->rgb.r);
    printf("%f\n",cyl->rgb.g);
    printf("%f\n",cyl->rgb.b);
    printf("%f\n",cyl->diameter);
    printf("%f\n",cyl->height);

}
tmp = tmp->next;
}
/*
tmp = tmp->next;
sphere_ptn = (t_sphere *)tmp->object;


printf("\n%f\n",sphere_ptn->origin.x);
printf("%f\n",sphere_ptn->origin.y);
printf("%f\n\n",sphere_ptn->origin.z);
printf("%f\n\n",sphere_ptn->rayon);
printf("%f\n",sphere_ptn->rgb.r);
printf("%f\n",sphere_ptn->rgb.g);
printf("%f\n",sphere_ptn->rgb.b);
printf("\n\n ---------\n");*/

    return(scene);
}