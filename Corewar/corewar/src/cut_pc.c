/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_pc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:35:38 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/30 19:12:10 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	del_buf(t_vm *vm, t_pc **buf)
{
	if (vm->v & 8)
	{
		ft_putstr("Process ");
		ft_putnbr((*buf)->id);
		ft_putstr(" hasn't lived for ");
		ft_putnbr(vm->cycles - (*buf)->cycle_alive);
		ft_putstr(" cycles (CTD ");
		ft_putnbr(vm->cycle_to_die);
		ft_putstr(")\n");
	}
	free(*buf);
}

static void	cut_pc(t_vm *vm)
{
	t_pc	*prev;
	t_pc	*pc;
	t_pc	*buf;

	prev = NULL;
	pc = vm->pc_lst;
	while (pc)
	{
		buf = pc;
		if ((vm->cycle_to_die <= 0
			|| vm->cycles - pc->cycle_alive >= vm->cycle_to_die) && vm->pcs--)
		{
			pc = pc->next;
			if (vm->pc_lst == buf)
				vm->pc_lst = pc;
			if (prev)
				prev->next = pc;
			del_buf(vm, &buf);
		}
		else
		{
			prev = pc;
			pc = pc->next;
		}
	}
}

static void	update_lives(t_vm *vm)
{
	unsigned int	i;

	i = 0;
	while (i < vm->players)
	{
		vm->champs[i]->prev_lives = vm->champs[i]->lives;
		vm->champs[i]->lives = 0;
		++i;
	}
	vm->lives_n = 0;
}

void		cycle_to_die_exec(t_vm *vm)
{
	cut_pc(vm);
	vm->checks++;
	if (vm->checks == MAX_CHECKS || vm->lives_n >= NBR_LIVE)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		if (vm->v & 2)
		{
			ft_putstr("Cycle to die is now ");
			ft_putnbr(vm->cycle_to_die);
			ft_putchar('\n');
		}
		vm->checks = 0;
	}
	update_lives(vm);
	vm->cycles_dup = 0;
}
