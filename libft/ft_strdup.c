/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:58:06 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/16 19:58:18 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		taille;
	char	*new;
	char	*debut;

	taille = ft_strlen(src);
	new = (char*)malloc(sizeof(char) * (taille + 1));
	if (new == 0)
		return (0);
	debut = new;
	while (*src != '\0')
	{
		*new = *src;
		new++;
		src++;
	}
	*new = '\0';
	return (debut);
}
