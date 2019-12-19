/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:29:11 by mdonchen          #+#    #+#             */
/*   Updated: 2019/07/26 11:07:42 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

void			print_ants(t_lst_ants *ants, t_lem *lem)
{
	t_lst_ants *tmp;

	tmp = ants;
	while (tmp)
	{
		tmp->pos = tmp->pos->next;
		tmp = tmp->next;
	}
	while (ants)
	{
		write(1, "L", 1);
		ft_putnbr(ants->id);
		write(1, "-", 1);
		ft_putstr(ants->pos->node->name);
		ants = ants->next;
		if (ants)
			write(1, " ", 1);
	}
}

unsigned int	ants_add_end(t_lst_ants **ants, t_lst_nodes *pos,
		unsigned int ants_end)
{
	t_lst_ants *tmp;

	if (!(*ants))
	{
		tmp = ft_memalloc(sizeof(t_lst_ants));
		tmp->id = ants_end;
		tmp->pos = pos;
		tmp->next = NULL;
		*ants = tmp;
	}
	else
	{
		tmp = *ants;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_memalloc(sizeof(t_lst_ants));
		tmp->next->id = ants_end;
		tmp->next->pos = pos;
		tmp->next->next = NULL;
	}
	return (ants_end);
}
