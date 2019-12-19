/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:37:43 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/15 14:18:22 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label	*find_lab(t_label *lst, char *name)
{
	t_label	*lab;

	lab = lst;
	while (lab)
	{
		if (!ft_strcmp(lab->name, name))
			return (lab);
		lab = lab->next;
	}
	return (lab);
}

t_label	*new_label(char *name, int op_i)
{
	t_label *lab;

	if (!(lab = (t_label*)ft_memalloc(sizeof(t_label))))
		asm_err(ERR_OOM);
	if (!(lab->name = ft_strdup(name)))
		asm_err(ERR_OOM);
	lab->op_i = op_i;
	return (lab);
}

void	add_label(t_label **lst, t_label *new)
{
	t_label *p;

	if (!lst)
		return ;
	if (*lst)
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
	else
		*lst = new;
}

void	mlabel_to_num(t_asm *asb)
{
	t_mlabel	*mlab;
	t_label		*lab;
	int			antoshka;

	lab = asb->labels;
	while (lab)
	{
		if (lab->op_i == -1)
			lab_err(lab);
		else
		{
			mlab = lab->mlabels;
			while (mlab)
			{
				antoshka = lab->op_i - mlab->op_i;
				if (mlab->size == 2)
					antoshka = (int16_t)antoshka;
				num_to_bytecode(asb->code, mlab->i, antoshka, mlab->size);
				mlab = mlab->next;
			}
		}
		lab = lab->next;
	}
}
