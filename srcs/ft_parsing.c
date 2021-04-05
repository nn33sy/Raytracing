/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  user42 <user42@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 13:31:46 by user42            #+#    #+#             */
/*   Updated: 2021/04/05 16:30:59 by  user42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		*ft_parsing_double(char *line, double *nb)
{
	while (*line && (*line == ' '))
		line++;
	*nb = ft_atoi_rt(line);
	if (*nb == -999)
		return (NULL);
	while (*line && ((*line >= '0' && *line <= '9') || (*line == '.')))
		line++;
	return (line);
}

int			ft_parsing_line(char *line, t_scene *scene)
{
	int res;

	res = 0;
	if (line[0] == 'R')
		res = ft_r(line, scene);
	if (line[0] == 's' && line[1] == 'p')
		res = ft_sp(line, scene);
	if (line[0] == 's' && line[1] == 'q')
		res = ft_sq(line, scene);
	if (line[0] == 'p')
		res = ft_p(line, scene);
	if (line[0] == 't' && line[1] == 'r')
		res = ft_tr(line, scene);
	if (line[0] == 'c' && line[1] == 'y')
		res = ft_cy(line, scene);
	if (line[0] == 'A')
		res = ft_a(line, scene);
	if (line[0] == 'c' && line[1] == ' ')
		res = ft_c(line, scene->camera);
	if (line[0] == 'l')
		res = ft_l(line, scene->light);
	return (res);
}

static void	ft_close_error(t_scene *scene, int fd)
{
	ft_clean_scene(scene);
	ft_putstr_fd("Error in the file or doesn't allocate", 1);
	free(scene);
	close(fd);
}

int			gnl_parsing(t_scene *scene, int fd)
{
	char	**line;

	line = (char**)malloc(sizeof(char *));
	if (line == NULL)
		return (0);
	while (get_next_line(fd, line) > 0)
	{
		if (ft_parsing_line(*line, scene) == -1)
		{
			ft_close_error(scene, fd);
			return (0);
		}
		free(*line);
	}
	if (ft_parsing_line(*line, scene) == -1)
	{
		ft_close_error(scene, fd);
		return (0);
	}
	free(*line);
	free(line);
	return (1);
}

t_scene		*main_parsing(char *file_scene)
{
	int		fd;
	t_scene	*scene;
	int		res;

	fd = open(file_scene, O_RDONLY);
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->light = malloc(sizeof(t_light *));
	*(scene->light) = NULL;
	scene->list = malloc(sizeof(t_list *));
	*(scene->list) = NULL;
	scene->camera = malloc(sizeof(t_camera *));
	*(scene->camera) = NULL;
	if (!scene || !(scene->light) || !(scene->list) || !(scene->camera))
	{
		ft_close_error(scene, fd);
		return (NULL);
	}
	res = gnl_parsing(scene, fd);
	close(fd);
	if (res == 0)
		return (NULL);
	return (scene);
}
