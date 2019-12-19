/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:29:42 by mdonchen          #+#    #+#             */
/*   Updated: 2019/07/26 13:42:29 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

void			reset_nodes(t_lst_nodes *lst, t_lem *lem)
{
	while (lst)
	{
		lst->node->q = 0;
		lst->node->fl = 0;
		lst->node->prev = NULL;
		lst = lst->next;
	}
	lem->start->fl = 0;
	lem->end->q = 1;
}

void			add_end_path(t_lst_paths **lst, t_lst_nodes *path)
{
	t_lst_paths *head;

	if (!(*lst))
	{
		head = ft_memalloc(sizeof(t_lst_paths));
		head->path = path;
		head->next = NULL;
		*lst = head;
		return ;
	}
	head = *lst;
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = ft_memalloc(sizeof(t_lst_paths));
	(*lst)->next->path = path;
	(*lst)->next->next = NULL;
	*lst = head;
}

t_lst_paths		*lem_paths(t_lem *lem)
{
	t_lst_paths	*path;
	t_lst_nodes	*lst;

	path = NULL;
	if (!link_unique(lem->start->links, lem->end))
	{
		lst = NULL;
		add_end_node(&lst, lem->start);
		add_end_node(&lst, lem->end);
		add_end_path(&path, lst);
		del_node(&lem->start->links, lem->end);
		del_node(&lem->end->links, lem->start);
	}
	while ((lst = b_f_s(lem)))
		add_end_path(&path, lst);
	return (path);
}
