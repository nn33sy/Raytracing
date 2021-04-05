#ifndef PARSING_H
# define PARSING_H
# include "minirt.h"

double		ft_atoi_rt(const char *str);
int			ft_r(char *line, t_scene *scene);
char		*ft_parsing_position(char *line, t_coord *coord);
char		*ft_parsing_rgb(t_rgb *rgb, char *line);
int			ft_c(char *line, t_camera **camera);
int			ft_a(char *line, t_scene *scene);
int			ft_l(char *line, t_light **light);
int			ft_r(char *line, t_scene *scene);
int			ft_sp(char *line, t_scene *scene);
int			ft_p(char *line, t_scene *scene);
int			ft_cy(char *line, t_scene *scene);
int			ft_sq(char *line, t_scene *scene);
int			ft_tr(char *line, t_scene *scene);
t_scene		*main_parsing(char *file_scene);
int			ft_parsing_line(char *line, t_scene *scene);
#endif
