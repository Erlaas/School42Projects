/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:37:50 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/16 12:40:38 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	champion_name(t_asm *asb, t_content **content)
{
	(*content) = (*content)->next;
	if ((*content)->type == STR)
	{
		if (!(asb->name = ft_strsub((*content)->content, 1,
			ft_strlen((*content)->content) - 2)))
			asm_err(ERR_OOM);
		if (ft_strlen(asb->name) > PROG_NAME_LENGTH)
		{
			ft_putstr_fd("Champion name too long, Max length: ", 2);
			ft_putnbr_fd(PROG_NAME_LENGTH, 2);
			ft_putstr_fd("\n", 2);
			exit(1);
		}
		(*content) = (*content)->next;
	}
	else
		content_err(*content);
}

void	champion_comment(t_asm *asb, t_content **content)
{
	(*content) = (*content)->next;
	if ((*content)->type == STR)
	{
		if (!(asb->comment = ft_strsub((*content)->content, 1,
			ft_strlen((*content)->content) - 2)))
			asm_err(ERR_OOM);
		if (ft_strlen(asb->comment) > COMMENT_LENGTH)
		{
			ft_putstr_fd("Champion comment too long, Max length: ", 2);
			ft_putnbr_fd(COMMENT_LENGTH, 2);
			ft_putstr_fd("\n", 2);
			exit(1);
		}
		(*content) = (*content)->next;
	}
	else
		content_err(*content);
}

void	pc_info(t_asm *asb, t_content **content)
{
	while (asb->name == NULL || asb->comment == NULL)
	{
		if ((*content)->type == COM && !asb->name &&
			!ft_strcmp((*content)->content, NAME_CMD_STRING))
		{
			champion_name(asb, content);
			if ((*content)->type != NL)
				content_err(*content);
		}
		else if ((*content)->type == COM && !asb->comment &&
			!ft_strcmp((*content)->content, COMMENT_CMD_STRING))
		{
			champion_comment(asb, content);
			if ((*content)->type != NL)
				content_err(*content);
		}
		else
			content_err(*content);
		(*content) = (*content)->next;
	}
}
