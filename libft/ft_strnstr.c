/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:09:38 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/25 13:29:45 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*needle == '\0')
		return ((char*)haystack);
	while ((haystack[i] != '\0') && (needle[j] != '\0') && i < len)
	{
		if (haystack[i] == needle[j])
			j++;
		else if (j > 0)
		{
			j = 0;
			i--;
		}
		i++;
	}
	if (j == ft_strlen(needle))
		return ((char*)(&haystack[i - j]));
	else
		return (0);
}
