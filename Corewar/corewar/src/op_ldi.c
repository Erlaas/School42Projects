/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:36:08 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/30 18:48:53 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	verbal_op(t_pc *pc, int kms[2], int r)
{
	ft_putstr("P ");
	ft_putnbr(pc->id);
	ft_putstr(" | ldi ");
	ft_putnbr(kms[0]);
	ft_putchar(' ');
	ft_putnbr(kms[1]);
	ft_putstr(" r");
	ft_putnbr(r);
	ft_putstr("\n       | -> load from ");
	ft_putnbr(kms[0]);
	ft_putstr(" + ");
	ft_putnbr(kms[1]);
	ft_putstr(" = ");
	ft_putnbr(kms[0] + kms[1]);
	ft_putstr(" (with pc and mod ");
	ft_putnbr(pc->pc + ((kms[0] + kms[1]) % IDX_MOD));
	ft_putstr(")\n");
}

void		op_ldi(t_vm *vm, t_pc *pc)
{
	int	kms[2];
	int	r;

	pc->jump += 2;
	kms[0] = read_value(vm, pc, 1, 1);
	kms[1] = read_value(vm, pc, 2, 1);
	r = read_byte(vm, pc->pc, pc->jump);
	pc->r[r - 1] = read_int(vm->map, (pc->pc + ((kms[0] + kms[1]) % IDX_MOD)),
	DIR_SIZE);
	pc->jump += 1;
	if (vm->v & 4)
		verbal_op(pc, kms, r);
}
