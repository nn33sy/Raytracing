/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:34:18 by how-choon         #+#    #+#             */
/*   Updated: 2020/12/10 14:34:23 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		l1;
	int		l2;
	int		i;
	int		j;
	char	*new;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if (!(new = (char*)malloc(sizeof(char) * (l1 + l2 + 1))))
		return (NULL);
	i = 0;
	while (l1 != 0 && i < l1)
	{
		new[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2 && ++j < l2)
	{
		new[i] = s2[j];
		i++;
	}
	new[i] = '\0';
	free(s1);
	return (new);
}

char	*ft_split_gnl(char **buffer, int stop)
{
	char	*result;
	char	*new_buffer;
	int		i;
	int		j;
	int		len_new_buffer;

	len_new_buffer = ft_strlen(*buffer) - stop - 1;
	if (!(result = (char*)malloc(sizeof(char) * (stop + 1))))
		return (NULL);
	if (!(new_buffer = (char*)malloc(sizeof(char) * (len_new_buffer + 1))))
		return (NULL);
	i = -1;
	while (++i < stop)
		result[i] = buffer[0][i];
	result[i++] = '\0';
	j = -1;
	while (++j < len_new_buffer)
	{
		new_buffer[j] = buffer[0][i];
		i++;
	}
	new_buffer[j] = '\0';
	free(*buffer);
	*buffer = new_buffer;
	return (result);
}

char	*ft_strdup(char *src)
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
