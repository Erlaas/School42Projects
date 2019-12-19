/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:37:55 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/15 13:37:54 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	read_label(t_asm *asb, t_content **content)
{
	t_label *label;
	char	*name;

	if (!(name = ft_strsub((*content)->content, 0,
		ft_strlen((*content)->content) - 1)))
		asm_err(ERR_OOM);
	if (!(label = find_lab(asb->labels, name)))
		add_label(&(asb->labels), new_label(name, asb->op_i));
	if (label && label->op_i == -1)
		label->op_i = asb->i;
	ft_strdel(&name);
	(*content) = (*content)->next;
}

static char	read_args(t_asm *asb, t_content **content, t_op *op)
{
	int		i;
	char	op_types;
	char	type;

	i = 0;
	op_types = 0;
	while (i < op->argc)
	{
		if ((*content)->type >= REG && (*content)->type <= INDIR_LAB)
		{
			type = read_arg(asb, content, op, i);
			update_op_types(&op_types, type, i);
			(*content) = (*content)->next;
		}
		else
			content_err(*content);
		if (i++ != (op->argc - 1))
		{
			if ((*content)->type != SEP)
				content_err(*content);
			(*content) = (*content)->next;
		}
	}
	return (op_types);
}

static void	read_op(t_asm *asb, t_content **content)
{
	t_op	*op;
	char	op_types;

	if ((op = get_op((*content)->content)))
	{
		asb->code[asb->i++] = op->op;
		(*content) = (*content)->next;
		if (op->read_argv)
			asb->i++;
		op_types = read_args(asb, content, op);
		if (op->read_argv)
			asb->code[asb->op_i + 1] = op_types;
	}
	else
		op_err(*content);
}

void		read_code(t_asm *asb, t_content **content)
{
	while ((*content)->type != END)
	{
		if (asb->i >= asb->size)
			update_code_buff(asb);
		asb->op_i = asb->i;
		if ((*content)->type == LBL)
			read_label(asb, content);
		if ((*content)->type == OP)
			read_op(asb, content);
		if ((*content)->type == NL)
			(*content) = (*content)->next;
		else
			content_err(*content);
	}
	if (asb->size == 0)
		asm_err("Champion should have at least one operation");
}
