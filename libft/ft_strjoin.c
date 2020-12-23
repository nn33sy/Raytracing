/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:12:30 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/16 18:26:05 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_check(const char *s1, const char *s2, int *l1, int *l2)
{
	if (s1 == NULL || s2 == NULL)
	{
		*l1 = 0;
		*l2 = -1;
	}
	else
	{
		*l1 = ft_strlen(s1);
		*l2 = ft_strlen(s2);
	}
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		l1;
	int		l2;
	int		i;
	int		j;
	char	*new;

	ft_check(s1, s2, &l1, &l2);
	new = (char*)malloc(sizeof(char) * (l1 + l2 + 1));
	if (new == 0)
		return (0);
	i = 0;
	while (l1 != 0 && i < l1)
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (l2 != 0 && j < l2)
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
