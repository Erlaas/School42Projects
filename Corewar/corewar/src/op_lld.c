/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:36:24 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/27 15:53:35 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	verbal_op(int id, int val, int r)
{
	ft_putstr("P ");
	ft_putnbr(id);
	ft_putstr(" | lld ");
	ft_putnbr(val);
	ft_putstr(" r");
	ft_putnbr(r);
	ft_putchar('\n');
}

void		op_lld(t_vm *vm, t_pc *pc)
{
	int	r;
	int	val;

	pc->jump += 2;
	val = read_value(vm, pc, 1, 0);
	pc->carry = (val == 0);
	r = read_byte(vm, pc->pc, pc->jump);
	pc->r[r - 1] = val;
	pc->jump += 1;
	if (vm->v & 4)
		verbal_op(pc->id, val, r);
}
