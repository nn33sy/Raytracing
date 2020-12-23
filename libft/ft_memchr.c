/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:44:13 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/26 14:58:47 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*chain;
	size_t			i;

	chain = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)c == chain[i])
			return (&chain[i]);
		i++;
	}
	return (0);
}
