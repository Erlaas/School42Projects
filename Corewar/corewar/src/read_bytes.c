/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:36:52 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/27 16:06:08 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		read_int(const unsigned char *map, int kms, int size)
{
	int		mask;
	int		ret;
	int		s;

	mask = 0;
	ret = 0;
	s = (map[mem_mod(kms)] & 0x80);
	while (size)
	{
		ret += ((s ? (map[mem_mod(kms + size - 1)] ^ 0xFF)
		: (map[mem_mod(kms + size - 1)])) << (mask++ * 8));
		--size;
	}
	if (s)
		ret = ~(ret);
	return (ret);
}

int		read_value(t_vm *vm, t_pc *pc, char i, int flag)
{
	t_op	*op;
	int		value;
	int		kms;

	op = &g_op_tab[pc->op - 1];
	if (pc->types[i - 1] & T_REG)
	{
		value = pc->r[read_byte(vm, pc->pc, pc->jump) - 1];
		pc->jump += 1;
	}
	else if (pc->types[i - 1] & T_DIR)
	{
		value = read_int(vm->map, pc->pc + pc->jump, op->dir_size);
		pc->jump += op->dir_size;
	}
	else if (pc->types[i - 1] & T_IND)
	{
		kms = read_int(vm->map, pc->pc + pc->jump, 2);
		value = read_int(vm->map, pc->pc + (flag ? (kms % IDX_MOD)
		: kms), DIR_SIZE);
		pc->jump += 2;
	}
	else
		value = 0;
	return (value);
}

int		mem_mod(int pc)
{
	if ((pc %= MEM_SIZE) < 0)
		pc += MEM_SIZE;
	return (pc);
}

char	read_byte(t_vm *vm, int pc, int step)
{
	return (vm->map[mem_mod(pc + step)]);
}
