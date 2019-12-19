/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_code_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:37:58 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/15 12:56:32 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_op		g_op_tab[16] = {
	{
		.op_name = "live",
		.op = 1,
		.argc = 1,
		.read_argv = 0,
		.argv = {T_DIR, 0, 0},
		.dir_size = 4,
	},
	{
		.op_name = "ld",
		.op = 2,
		.argc = 2,
		.read_argv = 1,
		.argv = {T_DIR | T_IND, T_REG, 0},
		.dir_size = 4,
	},
	{
		.op_name = "st",
		.op = 3,
		.argc = 2,
		.read_argv = 1,
		.argv = {T_REG, T_REG | T_IND, 0},
		.dir_size = 4,
	},
	{
		.op_name = "add",
		.op = 4,
		.argc = 3,
		.read_argv = 1,
		.argv = {T_REG, T_REG, T_REG},
		.dir_size = 4,
	},
	{
		.op_name = "sub",
		.op = 5,
		.argc = 3,
		.read_argv = 1,
		.argv = {T_REG, T_REG, T_REG},
		.dir_size = 4,
	},
	{
		.op_name = "and",
		.op = 6,
		.argc = 3,
		.read_argv = 1,
		.argv = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
	},
	{
		.op_name = "or",
		.op = 7,
		.argc = 3,
		.read_argv = 1,
		.argv = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
	},
	{
		.op_name = "xor",
		.op = 8,
		.argc = 3,
		.read_argv = 1,
		.argv = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
	},
	{
		.op_name = "zjmp",
		.op = 9,
		.argc = 1,
		.read_argv = 0,
		.argv = {T_DIR, 0, 0},
		.dir_size = 2,
	},
	{
		.op_name = "ldi",
		.op = 10,
		.argc = 3,
		.read_argv = 1,
		.argv = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.dir_size = 2,
	},
	{
		.op_name = "sti",
		.op = 11,
		.argc = 3,
		.read_argv = 1,
		.argv = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.dir_size = 2,
	},
	{
		.op_name = "fork",
		.op = 12,
		.argc = 1,
		.read_argv = 0,
		.argv = {T_DIR, 0, 0},
		.dir_size = 2,
	},
	{
		.op_name = "lld",
		.op = 13,
		.argc = 2,
		.read_argv = 1,
		.argv = {T_DIR | T_IND, T_REG, 0},
		.dir_size = 4,
	},
	{
		.op_name = "lldi",
		.op = 14,
		.argc = 3,
		.read_argv = 1,
		.argv = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.dir_size = 2,
	},
	{
		.op_name = "lfork",
		.op = 15,
		.argc = 1,
		.read_argv = 0,
		.argv = {T_DIR, 0, 0},
		.dir_size = 2,
	},
	{
		.op_name = "aff",
		.op = 16,
		.argc = 1,
		.read_argv = 1,
		.argv = {T_REG, 0, 0},
		.dir_size = 4,
	}
};

void					update_code_buff(t_asm *asb)
{
	asb->size += CHAMP_MAX_SIZE;
	if (!(asb->code = (char*)realloc(asb->code, ((size_t)asb->size + 14))))
		asm_err(ERR_OOM);
}

t_op					*get_op(char *name)
{
	unsigned		i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(g_op_tab[i].op_name, name))
			return (&g_op_tab[i]);
		++i;
	}
	return (NULL);
}

static unsigned char	get_op_typ(char typ)
{
	if (typ == T_DIR)
		return (DIR_CODE);
	else if (typ == T_REG)
		return (REG_CODE);
	return (IND_CODE);
}

void					update_op_types(char *op_types, char type, int i)
{
	(*op_types) |= (get_op_typ(type) << 2 * (4 - i - 1));
}
