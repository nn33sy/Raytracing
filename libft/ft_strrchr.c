/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:04:58 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/16 18:05:56 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	if (c == 0)
		return ((char*)&s[i]);
	while (i >= 0)
	{
		if (c == s[i])
			return ((char*)&s[i]);
		i--;
	}
	return (0);
}
