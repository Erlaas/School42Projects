/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:35:57 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/30 18:44:54 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	op_aff(t_vm *vm, t_pc *pc)
{
	int	r;
	int	val;

	pc->jump += 2;
	r = read_byte(vm, pc->pc, pc->jump);
	val = pc->r[r - 1];
	pc->jump += 1;
	if (vm->aff)
	{
		ft_putstr("Aff: ");
		ft_putchar((char)val);
		ft_putchar('\n');
	}
}
