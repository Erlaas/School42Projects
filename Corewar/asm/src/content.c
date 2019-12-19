/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:37:34 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/18 16:54:28 by vkhomenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_content	*new_content(t_asm *asb, t_type type)
{
	t_content	*content;

	if (!(content = (t_content*)ft_memalloc(sizeof(t_content))))
		asm_err(ERR_OOM);
	content->type = type;
	content->line = asb->line;
	content->c = asb->c - (type == SEP || type == NL);
	return (content);
}

void		add_content(t_content **contents, t_content *new)
{
	t_content		*p;

	if (!contents)
		return ;
	if (*contents)
	{
		p = *contents;
		while (p->next)
			p = p->next;
		((new->type == NL && p->type == NL)
		? (ft_memdel((void**)&new))
		: (p->next = new));
	}
	else
		((new->type == NL) ? (ft_memdel((void**)&new)) : (*contents = new));
}
