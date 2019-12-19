/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 12:08:46 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/30 19:11:40 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	add_pc(t_pc **pc_lst, t_pc *pc)
{
	if (pc)
		pc->next = *pc_lst;
	*pc_lst = pc;
}

t_pc	*new_pc(t_champion *owner, unsigned int pc)
{
	static unsigned int	pc_id;
	t_pc				*new;

	if (!(new = (t_pc*)ft_memalloc(sizeof(t_pc))))
		cor_err(ERR_OOM);
	pc_id++;
	new->id = pc_id;
	new->pc = pc;
	new->ch = owner;
	new->r[0] = -(owner->id);
	return (new);
}

t_pc	*cp_pc(t_pc *pc, int kms)
{
	t_pc	*cp_pc;
	int		i;

	kms = mem_mod(pc->pc + kms);
	cp_pc = new_pc(pc->ch, kms);
	cp_pc->carry = pc->carry;
	cp_pc->cycle_alive = pc->cycle_alive;
	i = 0;
	while (i < REG_NUMBER)
	{
		cp_pc->r[i] = pc->r[i];
		++i;
	}
	return (cp_pc);
}

void	create_pc(t_vm *vm)
{
	const int		jump = MEM_SIZE / vm->players;
	unsigned int	id;
	unsigned int	pc;

	pc = 0;
	id = 1;
	while (id <= vm->players)
	{
		add_pc(&(vm->pc_lst), new_pc(vm->champs[id - 1], pc));
		vm->pcs++;
		pc += jump;
		++id;
	}
}

void	move_pc(t_pc *pc)
{
	pc->pc += pc->jump;
	pc->pc = mem_mod(pc->pc);
	pc->jump = 0;
	pc->types[0] = 0;
	pc->types[1] = 0;
	pc->types[2] = 0;
}
