/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:36:43 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/27 15:56:43 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	verbal_op(int id, int val[2], int r)
{
	ft_putstr("P ");
	ft_putnbr(id);
	ft_putstr(" | xor ");
	ft_putnbr(val[0]);
	ft_putchar(' ');
	ft_putnbr(val[1]);
	ft_putstr(" r");
	ft_putnbr(r);
	ft_putchar('\n');
}

void		op_xor(t_vm *vm, t_pc *pc)
{
	int r;
	int res;
	int	val[2];

	pc->jump += 2;
	val[0] = read_value(vm, pc, 1, 1);
	val[1] = read_value(vm, pc, 2, 1);
	res = val[0] ^ val[1];
	pc->carry = (res == 0);
	r = read_byte(vm, pc->pc, pc->jump);
	pc->r[r - 1] = res;
	pc->jump += 1;
	if (vm->v & 4)
		verbal_op(pc->id, val, r);
}
