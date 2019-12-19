/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminates2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:38:05 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/15 12:38:14 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	arg_type_err(t_op *op, int i, t_content *content)
{
	ft_putstr_fd("Invalid type of parameter #", 2);
	ft_putnbr_fd(i + 1, 2);
	ft_putstr_fd(" for instruction \"", 2);
	ft_putstr_fd(op->op_name, 2);
	ft_putstr_fd("\" at [", 2);
	ft_putnbr_fd(content->line, 2);
	ft_putstr_fd(": ", 2);
	ft_putnbr_fd(content->c + 1, 2);
	ft_putstr_fd("]\n", 2);
	exit(1);
}

void	lab_err(t_label *lab)
{
	t_mlabel *mlab;

	ft_putstr_fd("Undeclared label \"", 2);
	ft_putstr_fd(lab->name, 2);
	ft_putstr_fd("\" is mentioned at: \n", 2);
	mlab = lab->mlabels;
	while (mlab)
	{
		ft_putstr_fd("\t- [", 2);
		ft_putnbr_fd(mlab->line, 2);
		ft_putstr_fd(": ", 2);
		ft_putnbr_fd(mlab->c + 1, 2);
		ft_putstr_fd("]\n", 2);
		mlab = mlab->next;
	}
	exit(1);
}
