/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:36:12 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/19 16:57:24 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	verbal_op(t_pc *pc, int kms)
{
	ft_putstr("P ");
	ft_putnbr(pc->id);
	ft_putstr(" | lfork ");
	ft_putnbr(kms);
	ft_putstr(" (");
	ft_putnbr(pc->pc + kms);
	ft_putstr(")\n");
}

void		op_lfork(t_vm *vm, t_pc *pc)
{
	t_pc	*dup;
	int		kms;

	pc->jump += 1;
	vm->pcs++;
	kms = read_value(vm, pc, 1, 1);
	dup = cp_pc(pc, kms);
	add_pc(&(vm->pc_lst), dup);
	if (vm->v & 4)
		verbal_op(pc, kms);
}
