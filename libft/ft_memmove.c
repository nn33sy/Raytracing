/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:42:36 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/19 23:26:57 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (!len || src == dst)
		return (dst);
	if (dst > src)
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			*(unsigned char*)(dst + i) = *(unsigned char*)(src + i);
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)len)
		{
			*(unsigned char *)(dst + i) = *(unsigned char*)(src + i);
			i++;
		}
	}
	return (dst);
}
