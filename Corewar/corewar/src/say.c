/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   say.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:31:26 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/30 19:02:13 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	verbal_pc_move(unsigned char *map, t_pc *pc)
{
	unsigned int i;

	ft_putstr("ADV ");
	ft_putnbr(pc->jump);
	ft_putstr(" (");
	printhex(pc->pc, 4);
	ft_putstr(" -> ");
	printhex(pc->pc + pc->jump, 4);
	ft_putstr(") ");
	i = 0;
	while (i < pc->jump)
	{
		printhex(map[mem_mod(pc->pc + i)], 4);
		ft_putchar(' ');
		++i;
	}
	ft_putchar('\n');
}

void	time_to_exec(t_vm *vm, t_pc *pc)
{
	if (pc->cycles_exec == 0)
	{
		pc->op = vm->map[pc->pc];
		if (vm->map[pc->pc] >= 1 && vm->map[pc->pc] <= 16)
			pc->cycles_exec = g_op_tab[pc->op - 1].cycles;
	}
}
