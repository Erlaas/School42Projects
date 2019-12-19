/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlabel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:37:48 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/15 12:38:14 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_mlabel	*new_mlabel(t_asm *asb, size_t siz)
{
	t_mlabel	*mlab;

	if (!(mlab = (t_mlabel*)ft_memalloc(sizeof(t_mlabel))))
		asm_err(ERR_OOM);
	mlab->line = asb->line;
	mlab->c = asb->c;
	mlab->i = asb->i;
	mlab->op_i = asb->op_i;
	mlab->size = siz;
	return (mlab);
}

void		add_mlabel(t_mlabel **lst, t_mlabel *new)
{
	t_mlabel *p;

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
