/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:12:46 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/18 18:21:00 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	cbis;
	char			*str;

	cbis = c;
	str = (char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = cbis;
		i++;
	}
	return (str);
}
