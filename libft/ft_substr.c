/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:56:33 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/18 18:51:06 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*sub;
	size_t		i;
	size_t		j;

	if (s == NULL)
		return (NULL);
	sub = (char*)malloc(sizeof(char) * (len + 1));
	if (sub == 0)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
	{
		sub[0] = '\0';
		return (sub);
	}
	i = start;
	j = 0;
	while (i != start + len && s[i] != '\0')
	{
		sub[j] = s[i];
		i++;
		j++;
	}
	sub[j] = '\0';
	return (sub);
}
