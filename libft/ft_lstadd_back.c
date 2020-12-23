/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:45:08 by how-choon         #+#    #+#             */
/*   Updated: 2020/11/16 19:45:48 by how-choon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *last;

	if (lst != NULL && new != NULL)
	{
		if (*lst != NULL)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
