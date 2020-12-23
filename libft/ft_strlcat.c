/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:58:45 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/18 21:59:03 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = ft_strlen(src);
	while (i < size && dst[i] != '\0')
		i++;
	dst_len = i;
	if (i == size)
	{
		dst_len = size;
		return (dst_len + src_len);
	}
	j = 0;
	while (src[j] && i < size - 1)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst_len + src_len);
}
