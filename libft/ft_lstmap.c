/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  user42 <user42@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:49:50 by how-choon         #+#    #+#             */
/*   Updated: 2021/04/06 08:53:19 by  user42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;

	if (lst == NULL || f == NULL)
		return (NULL);
	new = ft_lstnew(f(lst->object), 0);
	if (new == 0)
	{
		del(&(new->object));
		new = ft_lstmap(lst->next, f, del);
	}
	else
		new->next = ft_lstmap(lst->next, f, del);
	return (new);
}
