/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:37:53 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/15 14:17:25 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	arg_type(t_type type)
{
	if (type == DIRR || type == DIRR_LAB)
		return (T_DIR);
	else if (type == INDIR || type == INDIR_LAB)
		return (T_IND);
	else if (type == REG)
		return (T_REG);
	else
		return (0);
}

static void	pc_mlabel(t_asm *asb, t_content *content, t_op *op)
{
	const int	fl = (content->type == DIRR_LAB);
	size_t		siz;
	t_label		*lab;
	unsigned	strt;
	char		*name;

	strt = 1 + fl;
	siz = (fl) ? op->dir_size : IND_SIZE;
	if (!(name = ft_strsub(content->content, strt,
		ft_strlen(content->content) - strt)))
		asm_err(ERR_OOM);
	if (!(lab = find_lab(asb->labels, name)))
		add_label(&asb->labels, (lab = new_label(name, -1)));
	ft_strdel(&name);
	add_mlabel(&lab->mlabels, new_mlabel(asb, siz));
	asb->i += siz;
}

static void	pc_num(t_asm *asb, t_content *content, t_op *op)
{
	const int		fl = (content->type == DIRR);
	const unsigned	start = fl;
	const size_t	siz = (fl) ? op->dir_size : IND_SIZE;
	int				antoshka;

	antoshka = ft_atoi(&content->content[start]);
	if (siz == 2)
		antoshka = (int16_t)antoshka;
	else
		antoshka = (int32_t)antoshka;
	num_to_bytecode(asb->code, asb->i, antoshka, siz);
	asb->i += siz;
}

static void	pc_reg(t_asm *asb, t_content *content)
{
	char	antoshka;

	antoshka = (char)ft_atoi(&content->content[1]);
	num_to_bytecode(asb->code, asb->i, antoshka, 1);
	asb->i += 1;
}

char		read_arg(t_asm *asb, t_content **content, t_op *op, int i)
{
	const char t = arg_type((*content)->type);

	if (!(op->argv[i] & t))
		arg_type_err(op, i, *content);
	if ((*content)->type == INDIR_LAB || (*content)->type == DIRR_LAB)
		pc_mlabel(asb, *content, op);
	else if ((*content)->type == INDIR || (*content)->type == DIRR)
		pc_num(asb, *content, op);
	else
		pc_reg(asb, *content);
	return (t);
}
