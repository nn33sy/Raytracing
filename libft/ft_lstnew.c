/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:20:45 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/18 21:04:03 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, int type)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->next = NULL;
	new->object = content;
	return (new);
}
