/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:27:25 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/19 22:05:53 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charcomp(char const *set, char c)
{
	int i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_lentrim(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0' && ft_charcomp(set, s1[i]) == 1)
		i++;
	j = ft_strlen(s1) - 1;
	while (j >= i && ft_charcomp(set, s1[j]) == 1)
		j--;
	return (j - i + 1);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	int		length;
	int		i;
	int		j;

	if (s1 == 0 || set == 0)
		return (0);
	length = ft_lentrim(s1, set);
	s = (char *)malloc(sizeof(char) * (length + 1));
	if (s == 0)
		return (0);
	i = 0;
	j = 0;
	while (ft_charcomp(set, s1[i]) == 1)
		i++;
	while (j < length)
	{
		s[j] = s1[i];
		i++;
		j++;
	}
	s[j] = '\0';
	return (s);
}
