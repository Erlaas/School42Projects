/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:36:33 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/30 18:50:02 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	verbal_op(int id, int r, int kms)
{
	ft_putstr("P ");
	ft_putnbr(id);
	ft_putstr(" | st r");
	ft_putnbr(r);
	ft_putchar(' ');
	ft_putnbr(kms);
	ft_putchar('\n');
}

void		op_st(t_vm *vm, t_pc *pc)
{
	int	kms;
	int	r;
	int	r_val;

	pc->jump += 2;
	r = read_byte(vm, pc->pc, pc->jump);
	r_val = pc->r[r - 1];
	pc->jump += 1;
	if (pc->types[1] == T_REG)
	{
		kms = read_byte(vm, pc->pc, pc->jump);
		pc->r[kms - 1] = r_val;
		pc->jump += 1;
	}
	else
	{
		kms = read_int(vm->map, pc->pc + pc->jump, IND_SIZE);
		insert_int_map(vm->map, pc->pc + (kms % IDX_MOD), r_val, DIR_SIZE);
		pc->jump += IND_SIZE;
	}
	if (vm->v & 4)
		verbal_op(pc->id, r, kms);
}
