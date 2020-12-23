/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:03:24 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/18 21:48:12 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*chain;

	i = 0;
	chain = (char*)s;
	while (chain[i] != '\0')
	{
		if (chain[i] == c)
			return (&chain[i]);
		i++;
	}
	if (c == 0)
		return (&chain[i]);
	return (0);
}
