/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:36:20 by mdonchen          #+#    #+#             */
/*   Updated: 2019/09/25 13:38:50 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	verbal_op(int id, int player, t_champion *ch, int v)
{
	if (v & 4)
	{
		ft_putstr("P ");
		ft_putnbr(id);
		ft_putstr(" | live ");
		ft_putnbr(player);
		ft_putchar('\n');
	}
	if (v & 1 && ch)
	{
		ft_putstr("Player ");
		ft_putnbr(FT_ABS(player));
		ft_putstr(" (");
		ft_putstr(ch->name);
		ft_putstr(") is said to be alive\n");
	}
}

void		op_live(t_vm *vm, t_pc *pc)
{
	int			id;
	t_champion	*ch;

	ch = NULL;
	pc->jump += 1;
	id = read_value(vm, pc, 1, 0);
	vm->lives_n++;
	pc->cycle_alive = vm->cycles;
	if (id <= -1 && id >= -((int)vm->players))
	{
		ch = vm->champs[FT_ABS(id) - 1];
		ch->was_alive = vm->cycles;
		ch->lives++;
		vm->winner = ch;
	}
	verbal_op(pc->id, id, ch, vm->v);
}
