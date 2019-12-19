/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:36:47 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/30 19:43:35 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	verbal_op(t_pc *pc, int kms)
{
	ft_putstr("P ");
	ft_putnbr(pc->id);
	ft_putstr(" | zjmp ");
	ft_putnbr(kms);
	if (pc->carry)
		ft_putstr(" OK\n");
	else
		ft_putstr(" FAILED\n");
}

void		op_zjmp(t_vm *vm, t_pc *pc)
{
	int		kms;

	pc->jump += 1;
	kms = read_value(vm, pc, 1, 1);
	if (pc->carry)
	{
		pc->pc = mem_mod(pc->pc + (kms % IDX_MOD));
		pc->jump = 0;
	}
	if (vm->v & 4)
		verbal_op(pc, kms);
}
