#ifndef PARSING_H
# define PARSING_H
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include "function_maths.h"


double		ft_atoi_rt(const char *str);
int ft_r(char *line, t_scene *scene);
char *ft_parsing_position(char *line, t_coord *coord);
char *ft_parsing_rgb(t_rgb *rgb, char *line);
int ft_c(char *line, t_scene *scene);
int ft_a(char *line, t_scene *scene);
int ft_l(char *line,t_light *light);
int ft_sp(char *line, t_scene *scene);
int ft_p(char *line, t_scene *scene);
t_scene *main_parsing(void);

#endif