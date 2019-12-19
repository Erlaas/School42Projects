/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:47:04 by mdonchen          #+#    #+#             */
/*   Updated: 2018/10/28 18:24:30 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newl;

	if (!lst || !f)
		return (NULL);
	if (!(newl = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	newl = (*f)(lst);
	if (lst->next)
	{
		newl->next = ft_lstmap(lst->next, f);
		if (!(newl->next))
			return (NULL);
	}
	else
		newl->next = NULL;
	return (newl);
}
