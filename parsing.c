#include "function_maths.h"
# define BUFFER_SIZE 50
#include "parsing.h"
#include "gnl/get_next_line.h"

int ft_r(char *line, t_scene *scene)
{
    if (*line == 'R')
        line++;
    else 
        return(-1);
    while (*line && (*line == ' '))
        line++;
    if ((scene->r_x= ft_atoi(line)) == 0)
        return(-1);
    while (*line >= '0' && *line <= '9')
        line++;
    if ((scene->r_y= ft_atoi(line)) == 0)
        return(-1);
    return(1);
}
char *ft_parsing_position(char *line, t_coord *coord)
{
    coord->x = ft_atoi(line);
    while (*line && *line != ',')
        line++;
    line++;
    coord->y = ft_atoi(line);
    while (*line && *line != ',')
        line++;
    line++;
     coord->z = ft_atoi(line);
    while (*line && (((*line >= '0') && (*line <= '9')) || (*line == '.')))
        line++;
    return(line);
}
char *ft_parsing_rgb(s_rgb *rgb, char *line)
{
    rgb->r = ft_atoi(line);
    while (*line && (*line != ','))
        line++;
    if (*line)
        line++;
    rgb->g = ft_atoi(line);
     while (*line && (*line != ','))
        line++;
    if (*line)
        line++;
     rgb->b = ft_atoi(line);
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
    while (*line && (*line == ' '))
        line++;
    line = ft_parsing_position(line, &scene->camera.origin);
    while (*line && (*line == ' '))
        line++;
    line = ft_parsing_position(line, &scene->camera.direction);
     while (*line && (*line == ' '))
        line++;
    scene->fov = ft_atoi(line);
    return(1);
}
int ft_a(char *line, t_scene *scene)
{
    if (*line == 'A')
        line++;
    else
        return(-1);
    while (*line && (*line == ' '))
        line++;
    if ((scene->amb_light.ratio = ft_atoi(line)) < 0)
        return(-1);
     while ((*line >= '0' && *line <= '9') || (*line == '.'))
        line++;
    ft_parsing_rgb(&scene->amb_light.rgb,line);
    return(1);
}
int ft_l(char *line,t_light *light)
{
    if (*line != 'l')
        return (-1);
    line++;
    while (*line && (*line == ' '))
        line++;
    line = ft_parsing_position(line,&light->pos);
    while (*line && (*line == ' '))
        line++;
    light->i = ft_atoi(line);
    printf("%s",line);
    while (*line && ((*line >= '0' && *line <= '9') || (*line == '.')))
        line++;
    ft_parsing_rgb(&light->rgb,line);
    return(1);

}

int main()
{
    char *line[100];
    int i;
    i = 0;
while (i < 10)
{
    get_next_line(0, &line[i]);
    i++;
}
t_scene scene;
scene.light = malloc(sizeof(t_light *));
t_light light ;
*(scene.light) = &light;
i = 0;
ft_r(line[i],&scene);
i++;
ft_a(line[i],&scene);
i++;
/*printf("%f\n",scene.amb_light.ratio);
printf("%f\n",scene.amb_light.r);l
printf("%f\n",scene.amb_light.g);
printf("%f\n",scene.amb_light.b);*/
ft_c(line[i],&scene);
i++;
/*printf("%f\n",scene.camera.origin.x);
printf("%f\n",scene.camera.origin.y);
printf("%f\n",scene.camera.origin.z);
printf("%f\n",scene.camera.direction.x);
printf("%f\n",scene.camera.direction.y);
printf("%f\n",scene.camera.direction.z);
printf("%f\n",scene.fov);*/
while (*line[i] == 'l')
{
    ft_l(line[4],&light);

}


printf("%f\n",light.pos.x);
printf("%f\n",light.pos.y);
printf("%f\n",light.pos.z);
printf("%f\n",light.i);
printf("%f\n",light.rgb.r);
printf("%f\n",light.rgb.g);
printf("%f\n",light.rgb.b);

    return(0);
}