/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:34:49 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/18 18:33:22 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_2;
	unsigned char	*src_2;
	size_t			i;

	if (dst == 0 && src == 0)
		return (0);
	dst_2 = (unsigned char*)dst;
	src_2 = (unsigned char*)src;
	if (n > 0)
	{
		i = 0;
		while (i < n)
		{
			dst_2[i] = src_2[i];
			i++;
		}
	}
	return (dst_2);
}
