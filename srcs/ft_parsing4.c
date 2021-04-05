#include "minirt.h"

int			ft_cy(char *line, t_scene *scene)
{
	t_cylinder *cylinder;

	if (*line != 'c')
		return (-1);
	line++;
	if (*line != 'y')
		return (-1);
	line++;
	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return (-1);
	line = ft_parsing_position(line, &cylinder->base);
	line = ft_parsing_position(line, &cylinder->direction);
	line = ft_parsing_rgb(&cylinder->rgb, line);
	line = ft_parsing_double(line, &cylinder->diameter);
	line = ft_parsing_double(line, &cylinder->height);
	ft_lstadd_front(scene->list, ft_lstnew((void *)cylinder
	, 4, ft_atoi_rt(line)));
    if (line == NULL)
		return (-1);
	return (1);
}
