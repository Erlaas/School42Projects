/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:36:36 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/27 15:55:43 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	verbal_op(t_pc *pc, int r, int kms[2])
{
	ft_putstr("P ");
	ft_putnbr(pc->id);
	ft_putstr(" | sti r");
	ft_putnbr(r);
	ft_putchar(' ');
	ft_putnbr(kms[0]);
	ft_putchar(' ');
	ft_putnbr(kms[1]);
	ft_putstr("\n       | -> store to ");
	ft_putnbr(kms[0]);
	ft_putstr(" + ");
	ft_putnbr(kms[1]);
	ft_putstr(" = ");
	ft_putnbr(kms[0] + kms[1]);
	ft_putstr(" (with pc and mod ");
	ft_putnbr(pc->pc + ((kms[0] + kms[1]) % IDX_MOD));
	ft_putstr(")\n");
}

void		op_sti(t_vm *vm, t_pc *pc)
{
	int	r;
	int res;
	int	kms[2];

	pc->jump += 2;
	r = read_byte(vm, pc->pc, pc->jump);
	res = pc->r[r - 1];
	pc->jump += 1;
	kms[0] = read_value(vm, pc, 2, 1);
	kms[1] = read_value(vm, pc, 3, 1);
	insert_int_map(vm->map, (pc->pc + ((kms[0] + kms[1]) % IDX_MOD)), res,
	DIR_SIZE);
	if (vm->v & 4)
		verbal_op(pc, r, kms);
}
