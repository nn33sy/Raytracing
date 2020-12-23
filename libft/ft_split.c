/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:53:40 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/25 13:51:07 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_chain(char *str, int *size, char c)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (flag != 1)
	{
		while ((str[i] != '\0') && c != str[i])
			i++;
		if (i > 0)
			flag = 1;
		else
		{
			str++;
			i = 0;
		}
	}
	*size = i;
	return (str);
}

static int	count_lines(char *str, char c)
{
	int i;
	int count;

	count = 0;
	while (*str != '\0')
	{
		i = 0;
		while (*str && c == *str)
			str++;
		while (str[i] && c != str[i])
			i++;
		if (i)
			count++;
		str = str + i;
	}
	return (count);
}

static char	*copy(char *str, int size)
{
	int		i;
	char	*chain;

	i = 0;
	if (size == -1)
	{
		while (str[i] != '\0')
			i++;
		size = i;
	}
	if (!(chain = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		chain[i] = *str;
		str++;
		i++;
	}
	chain[i] = '\0';
	return (chain);
}

static char	**ft_check(char *str, char c, int *lines)
{
	char	**tab;

	if (str == NULL)
		return (NULL);
	*lines = count_lines(str, c);
	tab = (char**)malloc(sizeof(char*) * (*lines + 1));
	if (tab == 0)
		return (0);
	return (tab);
}

char		**ft_split(const char *s, char c)
{
	char	**tab;
	int		i;
	int		lines;
	int		size_chain;
	char	*str;

	i = 0;
	str = (char*)s;
	tab = ft_check(str, c, &lines);
	if (tab == NULL)
		return (NULL);
	while (i < lines)
	{
		str = find_chain(str, &size_chain, c);
		tab[i] = copy(str, size_chain);
		while (size_chain > 0)
		{
			size_chain--;
			str++;
		}
		i++;
	}
	tab[i] = 0;
	return (&tab[0]);
}
