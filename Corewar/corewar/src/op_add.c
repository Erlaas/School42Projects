/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:35:54 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/30 18:42:23 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	verbal_op(int id, int r[3])
{
	ft_putstr("P ");
	ft_putnbr(id);
	ft_putstr(" | add r");
	ft_putnbr(r[0]);
	ft_putchar(' ');
	ft_putnbr(r[1]);
	ft_putchar(' ');
	ft_putnbr(r[2]);
	ft_putchar('\n');
}

void		op_add(t_vm *vm, t_pc *pc)
{
	int r[3];
	int	val;

	pc->jump += 2;
	r[0] = read_byte(vm, pc->pc, pc->jump);
	pc->jump += 1;
	r[1] = read_byte(vm, pc->pc, pc->jump);
	pc->jump += 1;
	val = pc->r[r[0] - 1] + pc->r[r[1] - 1];
	pc->carry = (val == 0);
	r[2] = read_byte(vm, pc->pc, pc->jump);
	pc->r[r[2] - 1] = val;
	pc->jump += 1;
	if (vm->v & 4)
		verbal_op(pc->id, r);
}
