/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:35:30 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/20 15:25:34 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void		add_champion(t_champion **champs, t_champion *new)
{
	t_champion *tmp;

	if (champs && new)
	{
		if (!(*champs))
			*champs = new;
		else
		{
			tmp = *champs;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

void		update_ch_id(t_champion *ch)
{
	int			id;
	t_champion	*tmp;

	id = 1;
	tmp = ch;
	while (ch)
	{
		if (ch->id == 0)
		{
			while (is_champion(tmp, id))
				++id;
			ch->id = id;
		}
		ch = ch->next;
	}
}

t_champion	*is_champion(t_champion *ch, int n)
{
	t_champion *tmp;

	if (n < 1 || n > 4)
		return (NULL);
	tmp = ch;
	while (tmp)
	{
		if (tmp->id == n)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}
