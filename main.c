/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:07:40 by how-choongi       #+#    #+#             */
/*   Updated: 2021/04/07 19:07:41 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (argc == 2 && check_arg(argv[1]) == 1)
	{
		main_function(argv[1], 0);
		return (0);
	}
	if (argc == 3 &&
	ft_strncmp(argv[2], "--save", 5) == 0
	&& check_arg(argv[1]) == 1)
	{
		main_function(argv[1], 1);
		return (0);
	}
	ft_putstr_fd("Error", 1);
	return (0);
}
