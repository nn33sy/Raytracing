#include "minirt.h"

int	check_arg(char *arg)
{
	int size;

	size = ft_strlen(arg);
	if (arg[size - 1] != 't' || arg[size - 2] != 'r'
	|| arg[size - 3] != '.')
		return (-1);
	return (1);
}

int	main(int argc, char *argv[])
{
	if (argc == 2 || (argc == 3
	&& ft_strncmp(argv[2], "--save", ft_strlen("--save"))))
		if (check_arg(argv[1]) == 1)
			main_function(argv[1]);
		else
		{
			ft_putstr_fd("Error\n", 1);
			exit(EXIT_FAILURE);
		}
	else
	{
		ft_putstr_fd("Error\n", 1);
		exit(EXIT_FAILURE);
	}
}
