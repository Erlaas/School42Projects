/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:29:27 by mdonchen          #+#    #+#             */
/*   Updated: 2019/07/26 18:39:02 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

int		validate_link(char *str)
{
	int pipes;

	pipes = 0;
	while (*str)
	{
		if (*str == '-')
			pipes++;
		else if (*str == ' ')
			return (0);
		str++;
	}
	return (pipes == 1);
}

int		ft_lnkequ(char const *s1, char const *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s2[i])
		++i;
	return (s1[i] == '-' || s1[i] == '\0');
}

t_node	*find_link(int fl, char *str, t_lst_nodes *nodes)
{
	size_t i;

	i = 0;
	if (fl)
	{
		while (str[i] != '-')
			++i;
		++i;
	}
	while (nodes)
	{
		if (ft_lnkequ(str + i, nodes->node->name))
			return (nodes->node);
		nodes = nodes->next;
	}
	lem_err("ERROR: Can't find link room\n");
	return (NULL);
}

int		link_unique(t_lst_nodes *links, t_node *node)
{
	while (links)
	{
		if (links->node == node)
			return (0);
		links = links->next;
	}
	return (1);
}

void	read_link(char **str, t_lem *lem)
{
	t_node	*l1;
	t_node	*l2;

	if (!lem->start)
		lem_err("ERROR: Map has no start\n");
	if (!lem->end)
		lem_err("ERROR: Map has no end\n");
	if (!validate_link(*str))
		lem_err("ERROR: Wrong link, links example: room1-room2\n");
	if (ft_strequ(*str, "##start") || ft_strequ(*str, "##end"))
		lem_err("ERROR: Commands works only for rooms\n");
	l1 = find_link(0, *str, lem->nodes);
	l2 = find_link(1, *str, lem->nodes);
	if (l1 == l2)
		lem_err("ERROR: Wrong link, links example: room1-room2\n");
	if (link_unique(l1->links, l2) && link_unique(l1->links, l2))
	{
		add_end_node(&l1->links, l2);
		add_end_node(&l2->links, l1);
	}
	else
		lem_err("ERROR: Link not unique\n");
	ft_putstrdel(str);
}
