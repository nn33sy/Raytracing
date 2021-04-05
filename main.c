#include "minirt.h"

int	main(int argc, char *argv[])
{
	if (argc == 2 || (argc == 3
	&& ft_strncmp(argv[2], "--save", ft_strlen("--save"))))
		main_function(argv[1]);
	else
	{
		ft_putstr_fd("Error\n", 1);
		exit(EXIT_FAILURE);
	}
}
