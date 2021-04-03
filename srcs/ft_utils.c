#include "minirt.h"

void	ft_clean_rgb(t_palette *color_f)
{
	color_f->rgb.r = 0;
	color_f->rgb.g = 0;
	color_f->rgb.b = 0;
	color_f->intensity = 0;
}

double	ft_determinant_matrix(t_matrix_two *matrix)
{
	return ((matrix->x1 * matrix->y2) - (matrix->x2 * matrix->y1));
}
