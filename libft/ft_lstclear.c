/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:48:21 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/16 19:48:24 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (*lst != NULL)
	{
		if ((*lst)->next != NULL)
			ft_lstclear((&(*lst)->next), del);
		del((*lst)->content);
		free(*lst);
		*lst = NULL;
	}
}
