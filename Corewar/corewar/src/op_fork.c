/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:36:03 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/30 18:47:47 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	verbal_op(t_pc *pc, int kms)
{
	ft_putstr("P ");
	ft_putnbr(pc->id);
	ft_putstr(" | fork ");
	ft_putnbr(kms);
	ft_putstr(" (");
	ft_putnbr(pc->pc + kms % IDX_MOD);
	ft_putchar(')');
	ft_putchar('\n');
}

void		op_fork(t_vm *vm, t_pc *pc)
{
	int		kms;
	t_pc	*forkster;

	pc->jump += 1;
	vm->pcs++;
	kms = read_value(vm, pc, 1, 1);
	forkster = cp_pc(pc, kms % IDX_MOD);
	add_pc(&(vm->pc_lst), forkster);
	if (vm->v & 4)
		verbal_op(pc, kms);
}
