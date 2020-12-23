/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:03:00 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/19 22:07:47 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checklength(long n)
{
	int count;

	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	if (n < 10)
		count++;
	else
		count += 1 + ft_checklength(n / 10);
	return (count);
}

static void	ft_swap_chain(char *chain, int length)
{
	char inter;

	if (length >= 2)
	{
		inter = chain[0];
		chain[0] = chain[length - 1];
		chain[length - 1] = inter;
		ft_swap_chain(&chain[1], length - 2);
	}
}

static void	ft_ope(long n, char *chain)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		chain[i++] = '-';
		n *= -1;
	}
	if (n < 10)
	{
		chain[i++] = n + '0';
		chain[i] = '\0';
	}
	else
	{
		chain[i++] = (n % 10) + '0';
		ft_ope(n / 10, &chain[i]);
	}
}

char		*ft_itoa(int n)
{
	long	n2;
	long	length;
	char	*chain;

	n2 = (long)n;
	length = ft_checklength(n2);
	chain = (char *)malloc(sizeof(char) * (length + 1));
	if (chain == 0)
		return (0);
	ft_ope(n2, chain);
	if (n2 > 0)
		ft_swap_chain(chain, length);
	else
		ft_swap_chain(&chain[1], length - 1);
	return (chain);
}
