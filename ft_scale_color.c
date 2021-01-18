#include "libft.h"
#include "parsing.h"
#include "image.h"

void ft_scale_rgb(t_rgb *rgb)
{
    ft_scaling_one_value(&rgb->g);
    ft_scaling_one_value(&rgb->r);
    ft_scaling_one_value(&rgb->b);
}
void ft_scaling_one_value(double *value)
{
    if (*value > 255)
        *value = 255;
    if (*value < 0)
        *value = 0;
}
