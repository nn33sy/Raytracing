/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:30:56 by how-choon         #+#    #+#             */
/*   Updated: 2020/12/10 14:30:59 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		find_char(char *str)
{
	int	i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i] != '\0' && str[i] != 10)
		i++;
	if (str[i] == '\0')
		return (-1);
	return (1);
}

void	ft_read_line(t_list *ptn)
{
	char	buf[BUFFER_SIZE + 1];
	int		i;

	while ((i = read(ptn->fd, buf, BUFFER_SIZE)) >= 0)
	{
		buf[i] = 0;
		ptn->chain = ft_strjoin(ptn->chain, buf);
		if (i == 0 || find_char(ptn->chain) == 1)
			break ;
	}
}

t_list	*ft_list(t_list **list, int fd)
{
	t_list	*ptn;

	ptn = *list;
	while (ptn)
	{
		if (ptn->fd == fd)
		{
			ft_read_line(ptn);
			return (ptn);
		}
		ptn = ptn->next;
	}
	if (!(ptn = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	ptn->fd = fd;
	ptn->chain = NULL;
	ptn->next = *list;
	if (*list != NULL)
		(*list)->prec = ptn;
	ptn->prec = NULL;
	ft_read_line(ptn);
	*list = ptn;
	return (*list);
}

void	ft_free(t_list *ptn)
{
	free(ptn->chain);
	free(ptn);
}

int		get_next_line(int fd, char **line)
{
	char			buf[1];
	static t_list	*list;
	t_list			*ptn;
	int				i;

	if (fd < 0 || !line || (read(fd, buf, 0) < 0) ||
!(ptn = ft_list(&list, fd)) || BUFFER_SIZE <= 0)
		return (-1);
	i = 0;
	while (ptn->chain[i] != '\0' && ptn->chain[i] != 10)
		i++;
	if (ptn->chain[i] != '\0')
	{
		*line = ft_split_gnl((&ptn->chain), i);
		return (1);
	}
	*line = ft_strdup(ptn->chain);
	if (ptn->prec != NULL)
		ptn->prec->next = ptn->next;
	if (ptn->next != NULL)
		ptn->next->prec = ptn->prec;
	if (list == ptn)
		list = (ptn->next == 0) ? ptn->prec : ptn->next;
	ft_free(ptn);
	return (0);
}
