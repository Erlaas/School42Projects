/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_f_s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:29:16 by mdonchen          #+#    #+#             */
/*   Updated: 2019/07/26 12:57:28 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

t_lst_nodes	*ret_path(t_lst_nodes *path, t_node *node)
{
	t_lst_nodes *head;

	head = path;
	if (path)
	{
		while (path->next)
		{
			while (path->next->next)
				path = path->next;
			free(path->next);
			path->next = NULL;
			path = head;
		}
		free(path);
	}
	head = NULL;
	while (node)
	{
		add_end_node(&head, node);
		node->fl = 1;
		node = node->prev;
	}
	return (head);
}

void		links_pepega(t_lst_nodes *links, t_lst_nodes **bfs, t_node *node)
{
	while (links)
	{
		if (!links->node->q && !links->node->fl)
		{
			links->node->q = 1;
			links->node->prev = node;
			add_end_node(bfs, links->node);
		}
		links = links->next;
	}
}

t_node		*cut_node(t_lst_nodes **lst)
{
	t_node		*node;
	t_lst_nodes	*tmp;

	node = NULL;
	if (lst)
	{
		tmp = *lst;
		node = (*lst)->node;
		*lst = (*lst)->next;
		free(tmp);
		tmp = NULL;
	}
	return (node);
}

t_lst_nodes	*b_f_s(t_lem *lem)
{
	t_lst_nodes	*bfs;
	t_node		*node;

	bfs = lem->nodes;
	while (bfs)
	{
		bfs->node->q = 0;
		bfs->node->prev = NULL;
		bfs = bfs->next;
	}
	lem->start->fl = 0;
	lem->end->q = 1;
	bfs = ft_memalloc(sizeof(t_lst_nodes));
	bfs->node = lem->end;
	bfs->next = NULL;
	while (bfs)
	{
		node = cut_node(&bfs);
		if (node == lem->start)
			return (ret_path(bfs, lem->start));
		else
			links_pepega(node->links, &bfs, node);
	}
	return (NULL);
}
