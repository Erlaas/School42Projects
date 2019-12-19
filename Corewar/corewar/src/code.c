/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:35:32 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/30 19:07:49 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static int	is_reg(t_vm *vm, int pc, int jump)
{
	char r;

	r = read_byte(vm, pc, jump);
	return (r >= 1 && r <= REG_NUMBER);
}

int			args_valid(t_pc *pc, t_vm *vm, t_op *op)
{
	const unsigned char	tmp = op->argc;
	unsigned int		step;
	unsigned int		jump;
	int					i;

	i = 0;
	jump = 1 + op->read_argv;
	while (i < tmp)
	{
		if ((pc->types[i] == T_REG) && !is_reg(vm, pc->pc, jump))
			return (0);
		step = 0;
		if (pc->types[i] & T_REG)
			step = 1;
		else if (pc->types[i] & T_DIR)
			step = op->dir_size;
		else if (pc->types[i] & T_IND)
			step = 2;
		jump += step;
		++i;
	}
	return (1);
}

int			calc_jump(t_pc *pc, t_op *op)
{
	const unsigned char	tmp = g_op_tab[pc->op - 1].argc;
	unsigned int		j;
	unsigned int		step;
	int					i;

	i = 0;
	j = 1 + op->read_argv;
	while (i < tmp)
	{
		step = 0;
		if (pc->types[i] & T_REG)
			step = 1;
		else if (pc->types[i] & T_DIR)
			step = op->dir_size;
		else if (pc->types[i] & T_IND)
			step = 2;
		j += step;
		++i;
	}
	return (j);
}

void		insert_int_map(unsigned char *map, int kms, int val, int size)
{
	char	i;

	i = 0;
	while (size)
	{
		map[mem_mod(kms + size - 1)] = (unsigned char)((val >> i) & 0xFF);
		--size;
		i = i + 8;
	}
}
