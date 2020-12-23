/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:52:42 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/18 18:49:09 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*chain;

	if (size == 0 || count == 0)
	{
		count = 1;
		size = 1;
	}
	chain = malloc(size * count);
	if (chain == 0)
		return (0);
	ft_bzero(chain, (count * size));
	return (chain);
}
