/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:37:54 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/18 18:26:17 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_2;
	unsigned char	*src_2;
	unsigned char	c2;
	size_t			i;

	dst_2 = (unsigned char*)dst;
	src_2 = (unsigned char*)src;
	c2 = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		dst_2[i] = src_2[i];
		if (c2 == src_2[i])
			return (&dst_2[i + 1]);
		i++;
	}
	return (0);
}
