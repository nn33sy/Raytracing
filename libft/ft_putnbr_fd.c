/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:18:18 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/18 21:43:38 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	n2;

	n2 = (long)n;
	if (n2 < 0)
	{
		n2 *= -1;
		ft_putstr_fd("-", fd);
	}
	if (n2 < 10)
		ft_putchar_fd(n2 + '0', fd);
	else
	{
		ft_putnbr_fd(n2 / 10, fd);
		ft_putchar_fd(n2 % 10 + '0', fd);
	}
}
