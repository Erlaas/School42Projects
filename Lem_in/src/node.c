/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:29:35 by mdonchen          #+#    #+#             */
/*   Updated: 2019/07/26 14:49:39 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

void	unique_coordinates(t_node *n1, t_node *n2)
{
	if (ft_strequ(n1->name, n2->name))
		lem_err("ERROR: Rooms name not unique\n");
	if (n1->xy[0] == n2->xy[0] && n1->xy[1] == n2->xy[1])
		lem_err("ERROR: Room coordinate not unique\n");
}

void	add_end_node(t_lst_nodes **lst, t_node *node)
{
	t_lst_nodes *tmp;

	if (!(*lst))
	{
		tmp = ft_memalloc(sizeof(t_lst_nodes));
		tmp->node = node;
		tmp->next = NULL;
		*lst = tmp;
		return ;
	}
	tmp = *lst;
	while (tmp)
	{
		unique_coordinates(tmp->node, node);
		tmp = tmp->next;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_memalloc(sizeof(t_lst_nodes));
	tmp->next->node = node;
	tmp->next->next = NULL;
}

void	del_node(t_lst_nodes **lst, t_node *node)
{
	t_lst_nodes	*head;
	t_lst_nodes	*tmp;

	tmp = NULL;
	if ((*lst)->node != node)
	{
		head = *lst;
		while (head->next)
		{
			if (head->next->node == node)
			{
				tmp = head->next;
				head->next = head->next->next;
				free(tmp);
				return ;
			}
			head = head->next;
		}
	}
	else
	{
		tmp = *lst;
		*lst = (*lst)->next;
	}
	free(tmp);
}
