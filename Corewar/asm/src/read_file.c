/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:38:01 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/15 12:41:13 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned	jump_spaces_comments(unsigned c, char *str)
{
	while (ft_isspace(str[c]))
		++c;
	if (str[c] == COMMENT_CHAR)
		while (str[c] != '\n' && str[c])
			++c;
	return (c);
}

static void		read_num(t_asm *asb, char *gnl, unsigned i, t_content *content)
{
	unsigned c;

	content->c = i;
	if (gnl[asb->c] == '-')
		++asb->c;
	c = asb->c;
	while (ft_isdigit(gnl[asb->c]))
		++asb->c;
	if ((asb->c - c) && (content->type == DIRR || ft_isdelim(gnl[asb->c])))
	{
		if (!(content->content = ft_strsub(gnl, i, asb->c - i)))
			asm_err(ERR_OOM);
		add_content(&asb->contents, content);
	}
	else if (content->type != DIRR)
	{
		asb->c = i;
		read_symbols(asb, gnl, i, content);
	}
	else
		asm_lexical_err(asb);
}

static void		read_dir(t_asm *asb, char **gnl)
{
	if ((*gnl)[asb->c] == LABEL_CHAR && ++asb->c)
		read_symbols(asb, *gnl, asb->c - 2, new_content(asb, DIRR_LAB));
	else
		read_num(asb, *gnl, asb->c - 1, new_content(asb, DIRR));
}

static void		read_content(t_asm *asb, char **gnl)
{
	if (!(*gnl)[asb->c])
		return ;
	else if ((*gnl)[asb->c] == SEPARATOR_CHAR && ++asb->c)
		add_content(&asb->contents, new_content(asb, SEP));
	else if ((*gnl)[asb->c] == '\n' && ++asb->c)
		add_content(&asb->contents, new_content(asb, NL));
	else if ((*gnl)[asb->c] == '.')
		read_symbols(asb, *gnl, asb->c++, new_content(asb, COM));
	else if ((*gnl)[asb->c] == DIRECT_CHAR && ++asb->c)
		read_dir(asb, gnl);
	else if ((*gnl)[asb->c] == '\"')
		read_str(asb, gnl, asb->c, new_content(asb, STR));
	else if ((*gnl)[asb->c] == LABEL_CHAR)
		read_symbols(asb, *gnl, asb->c++, new_content(asb, INDIR_LAB));
	else
		read_num(asb, *gnl, asb->c, new_content(asb, INDIR));
}

void			read_file(t_asm *asb, int fd)
{
	ssize_t		r;
	char		*gnl;
	t_content	*con;

	asb->fd = fd;
	while ((r = gnl_asm(fd, &gnl)) > 0)
	{
		asb->line++;
		asb->c = 0;
		while (gnl[asb->c])
		{
			asb->c = jump_spaces_comments(asb->c, gnl);
			read_content(asb, &gnl);
		}
		free(gnl);
	}
	if (r == -1)
		asm_err(ERR_FILE);
	add_content(&(asb->contents), new_content(asb, END));
	con = asb->contents;
	pc_info(asb, &con);
	read_code(asb, &con);
	mlabel_to_num(asb);
}
