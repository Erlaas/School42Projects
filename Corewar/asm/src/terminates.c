/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminates.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:38:04 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/16 13:01:18 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_lexical_err(t_asm *asb)
{
	ft_putstr_fd("Lexical error [", 2);
	ft_putnbr_fd(asb->line, 2);
	ft_putstr_fd(": ", 2);
	ft_putnbr_fd(asb->c + 1, 2);
	ft_putstr_fd("]\n", 2);
	exit(1);
}

void	asm_err(char *str)
{
	if (errno != 0)
		perror(str);
	else
		ft_putendl_fd(str, 2);
	exit(1);
}

void	content_err(t_content *content)
{
	if (content->type == END)
		ft_putstr_fd("Unexpected end of input (Perhaps you forgot to end with"\
				" a newline ?)\n", 2);
	else
	{
		ft_putstr_fd("Unexpected token \"", 2);
		ft_putstr_fd(content->content, 2);
		ft_putstr_fd("\" at [", 2);
		ft_putnbr_fd(content->line, 2);
		ft_putstr_fd(": ", 2);
		ft_putnbr_fd(content->c + 1, 2);
		ft_putstr_fd("]\n", 2);
	}
	exit(1);
}

void	op_err(t_content *content)
{
	ft_putstr_fd("Unknown operator \"", 2);
	ft_putstr_fd(content->content, 2);
	ft_putstr_fd("\" at [", 2);
	ft_putnbr_fd(content->line, 2);
	ft_putstr_fd(": ", 2);
	ft_putnbr_fd(content->c + 1, 2);
	ft_putstr_fd("]\n", 2);
	exit(1);
}

void	usage(char *str)
{
	ft_putstr("Usage: ");
	ft_putstr(str);
	ft_putstr(" <champion.s>\n");
	exit(0);
}
