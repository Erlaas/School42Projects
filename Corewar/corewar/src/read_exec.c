/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:36:55 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/30 19:18:33 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	get_arg(char type, char i, t_pc *pc)
{
	const unsigned char arg_tab[3] = {T_REG, T_DIR, T_IND};

	pc->types[(int)i] = arg_tab[type - 1];
}

static void	get_types(t_vm *vm, t_pc *pc, t_op *op)
{
	char	types_arg;

	if (op->read_argv)
	{
		types_arg = read_byte(vm, pc->pc, 1);
		if (op->argc > 0)
		{
			get_arg((types_arg & 0xC0) >> 6, 0, pc);
			if (op->argc > 1)
			{
				get_arg((types_arg & 0x30) >> 4, 1, pc);
				if (op->argc == 3)
					get_arg((types_arg & 0xC) >> 2, 2, pc);
			}
		}
	}
	else
		pc->types[0] = op->argv[0];
}

static int	types_valid(t_pc *pc, t_op *op)
{
	int i;

	i = 0;
	while (i < op->argc)
	{
		if (!(pc->types[i] & op->argv[i]))
			return (0);
		++i;
	}
	return (1);
}

static void	exec_op(t_pc *pc, t_vm *vm)
{
	t_op *op;

	time_to_exec(vm, pc);
	if (pc->cycles_exec > 0)
		pc->cycles_exec--;
	if (pc->cycles_exec == 0)
	{
		op = NULL;
		if (pc->op >= 1 && pc->op <= 16)
		{
			op = &g_op_tab[pc->op - 1];
			get_types(vm, pc, op);
			if (types_valid(pc, op) && args_valid(pc, vm, op))
				op->function(vm, pc);
			else
				pc->jump += calc_jump(pc, op);
			if (vm->v & 16 && pc->jump)
				verbal_pc_move(vm->map, pc);
		}
		else
			pc->jump = 1;
		move_pc(pc);
	}
}

void		exec_check(t_vm *vm)
{
	t_pc *tmp;

	vm->cycles++;
	vm->cycles_dup++;
	if (vm->v & 2)
	{
		ft_putstr("Cycle num ");
		ft_putnbr(vm->cycles);
		ft_putchar('\n');
	}
	tmp = vm->pc_lst;
	while (tmp)
	{
		exec_op(tmp, vm);
		tmp = tmp->next;
	}
}
