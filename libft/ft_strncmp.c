/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:06:20 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/18 19:09:22 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_2;
	unsigned char	*s2_2;

	i = 0;
	s1_2 = (unsigned char*)s1;
	s2_2 = (unsigned char*)s2;
	if (n == 0)
		return (0);
	while ((s1_2[i]) && (s2_2[i]) && (i < n - 1) && (s1_2[i] == s2_2[i]))
		i++;
	return (s1_2[i] - s2_2[i]);
}
